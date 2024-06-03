from urllib.parse import urlencode
from rest_framework.request import Request

from rest_framework.decorators import permission_classes
from rest_framework import status
from rest_framework.permissions import AllowAny
import os
import json
import requests
from rest_framework.decorators import api_view
from rest_framework_simplejwt.tokens import RefreshToken as BaseRefreshToken
from trench.exceptions import MFAValidationError, MFAMethodDoesNotExistError
from trench.responses import ErrorResponse
from trench.serializers import MFAMethodActivationConfirmationValidator
from .forms import CreateUserForm
from .models import CustomUser
from trench.views import (
    MFAFirstStepMixin,
    MFASecondStepMixin,
    MFAStepMixin,
    User,
)
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.status import HTTP_400_BAD_REQUEST
from rest_framework.views import APIView
from .backends import activate_mfa_method_command
import hashlib
import hmac
import os
from trench.utils import get_mfa_model, user_token_generator
from trench.backends.provider import get_mfa_handler


class CustomActivateMFAView(APIView):
    permission_classes = (IsAuthenticated,)

    @staticmethod
    def post(request: Request, method: str) -> Response:
        serializer = MFAMethodActivationConfirmationValidator(
            mfa_method_name=method, user=request.user, data=request.data
        )
        if not serializer.is_valid():
            return Response(status=HTTP_400_BAD_REQUEST, data=serializer.errors)
        try:
            backup_codes = activate_mfa_method_command(
                user_id=request.user.id,
                name=method,
                code=serializer.validated_data["code"],
            )
            return Response({"backup_codes": backup_codes})
        except MFAValidationError as cause:
            return ErrorResponse(error=cause)


class CustomMFAJWTView(MFAStepMixin):
    def _successful_authentication_response(self, user: User) -> Response:
        token = RefreshToken.for_user(user=user)
        return Response(data={"refresh": str(token), "access": str(token.access_token)})


class CustomMFAFirstStepJWTView(CustomMFAJWTView, MFAFirstStepMixin):
    pass


class CustomMFASecondStepJWTView(CustomMFAJWTView, MFASecondStepMixin):
    pass


def get_tokens_for_user(user):
    refresh = RefreshToken.for_user(user)

    return {
        "refresh": str(refresh),
        "access": str(refresh.access_token),
    }


class RefreshToken(BaseRefreshToken):
    @classmethod
    def for_user(cls, user):
        token = super().for_user(user)

        # Add custom claims
        token["username"] = user.username
        # ...

        return token


@api_view(["POST"])
@permission_classes([AllowAny])
def register_api(request):
    data = json.loads(request.body)
    form = CreateUserForm(data)
    if form.is_valid():
        user = form.save()
        tokens = get_tokens_for_user(user)
        return Response(
            {"access": tokens["access"], "refresh": tokens["refresh"]},
        )
    else:
        errors = {field: form.errors[field][0] for field in form.errors}
        print("INVALID registration")
        print(errors)
        return Response({"errors": errors}, status=status.HTTP_400_BAD_REQUEST)


def get_unique_username(username):
    counter = 0
    new_username = username
    while CustomUser.objects.filter(username=new_username).exists():
        counter += 1
        new_username = f"{username}_{counter}"
    return new_username


@api_view(["POST"])
def oauth_42(request):
    body_unicode = request.body.decode("utf-8")
    body = json.loads(body_unicode)
    code = body["code"]
    url = "https://api.intra.42.fr/oauth/token"
    data = {
        "grant_type": "authorization_code",
        "client_id": os.getenv("CLIENT_ID"),
        "client_secret": os.getenv("CLIENT_SECRET"),
        "code": code,
        "redirect_uri": os.getenv("REDIRECT_URI"),
    }
    response = requests.post(url, data=data)
    if response.status_code == 200:
        access_token = response.json()["access_token"]
        headers = {"Authorization": f"Bearer {access_token}"}
        user_data = requests.get("https://api.intra.42.fr/v2/me", headers=headers)
        userinfo = user_data.json()
        if user_data.status_code == 200:
            external_id = userinfo["id"]
            user_email = userinfo["email"]
            user_login = userinfo["login"]
            user_image = userinfo["image"]["link"]
            username = get_unique_username(user_login)
            user, created = CustomUser.objects.get_or_create(
                external_id=external_id,
                defaults={
                    "username": username,
                    "email": user_email,
                    "profile_image": user_image,
                },
            )
            if user is not None:
                try:
                    mfa_model = get_mfa_model()
                    mfa_method = mfa_model.objects.get_primary_active(user_id=user.id)
                    get_mfa_handler(mfa_method=mfa_method).dispatch_message()
                    ephemeral_token = user_token_generator.make_token(user)
                    print(ephemeral_token)
                    return Response(
                        data={
                            "ephemeral_token": ephemeral_token,
                            "method": mfa_method.name,
                        },
                        status=202,
                    )
                except MFAMethodDoesNotExistError as cause:
                    tokens = get_tokens_for_user(user)
                    return Response(
                        {"access": tokens["access"], "refresh": tokens["refresh"]},
                        status=200,
                    )
        else:
            return Response(
                {"message": "Failed to get user data from 42 server"}, status=500
            )
    else:
        print(f"POST request failed with status code {response.status_code}")
        return Response(
            {"message": "Failed to get access token from the 42 server"}, status=500
        )


@api_view(["GET"])
@permission_classes([AllowAny])
def auth_42(request):
    data = {
        "client_id": os.getenv("CLIENT_ID"),
        "response_type": "code",
        "redirect_uri": os.getenv("REDIRECT_URI"),
    }
    url_params = urlencode(data)
    auth_url = f"https://api.intra.42.fr/oauth/authorize?{url_params}"
    return Response({"url": auth_url}, status=status.HTTP_200_OK)
