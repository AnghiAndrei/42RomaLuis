import os

from rest_framework.decorators import api_view, permission_classes
from rest_framework.response import Response
from .models import CustomUser
from .serializers import CustomUserSerializer, UserInfoSerializer, UserFriendsSerializer
import logging
from rest_framework.permissions import IsAuthenticated
from django.core.files.images import ImageFile
from email_validator import validate_email, EmailNotValidError
from django.contrib.auth.password_validation import validate_password
from django.core.exceptions import ValidationError
import re

# Configura il logger
logger = logging.getLogger(__name__)


@api_view(["GET"])
@permission_classes([IsAuthenticated])
def available_users(request):
    users = (
        CustomUser.objects.all()
        .exclude(is_superuser=True)
        .exclude(id=request.user.id)
        .exclude(id__in=request.user.friends.values_list("id", flat=True))
    )
    serializer = UserFriendsSerializer(users, many=True, context={"request": request})
    return Response(serializer.data)


@api_view(["GET"])
@permission_classes([IsAuthenticated])
def user_friends(request):
    user = request.user
    friends = user.friends.all()
    serializer = UserFriendsSerializer(friends, many=True, context={"request": request})
    return Response(serializer.data)


@api_view(["GET"])
@permission_classes([IsAuthenticated])
def user_info(request):
    user = request.user
    serializer = UserInfoSerializer(user)
    return Response(serializer.data)


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def update_username(request):
    try:
        user = request.user
        data = request.data
        if "username" in data:
            new_username = data["username"]
            if (
                CustomUser.objects.filter(username=new_username)
                .exclude(pk=user.pk)
                .exists()
            ):
                return Response({"message": "Username is already in use"}, status=400)
            user.username = new_username
        user.save()
        return Response({"message": "User updated successfully"})
    except Exception as e:
        logger.error(e)
        return Response({"message": "Error updating user"}, status=500)


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def update_email(request):
    try:
        user = request.user
        data = request.data
        if "email" in data:
            new_email = data["email"]
            try:
                validate_email(new_email)
                if (
                    CustomUser.objects.filter(email=new_email)
                    .exclude(pk=user.pk)
                    .exists()
                ):
                    return Response({"message": "Email is already in use"}, status=400)
                user.email = new_email
            except EmailNotValidError as e:
                return Response({"message": str(e)}, status=400)
        user.save()
        return Response({"message": "User updated successfully"})
    except Exception as e:
        logger.error(e)
        return Response({"message": "Error updating user"}, status=500)


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def update_password(request):
    try:
        user = request.user
        data = request.data
        if "password" in data:
            password = data["password"]
            try:
                # Validate the password
                validate_password(password, user)
                user.set_password(password)
            except ValidationError as e:
                return Response({"message": str(e)}, status=400)
        user.save()
        return Response({"message": "User updated successfully"})
    except Exception as e:
        logger.error(e)
        return Response({"message": "Error updating user"}, status=500)


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def update_image(request):
    try:
        user = request.user
        image_url = request.data.get(
            "avatar", None
        )  # get the image URL from the request

        if image_url is not None:
            user.profile_image = image_url
            user.save()
            return Response({"message": "User updated successfully"})
        else:
            return Response({"message": "No image URL provided"}, status=400)

    except Exception as e:
        logger.error(e)
        return Response({"message": "Error updating user"}, status=500)


@api_view(["GET"])
@permission_classes([IsAuthenticated])
def player_info(request, player_id):
    print("player_id")
    player = CustomUser.objects.get(id=player_id)
    if player:
        serializer = UserInfoSerializer(player)
        return Response(serializer.data)
    else:
        return Response({"message": "Player not found"}, status=404)


@api_view(["GET"])
def diocane(request):
    return Response({"message": "diocaneaSSS"}, status=203)
