from django.contrib.auth.hashers import make_password
from django.http import JsonResponse, HttpResponse
from django.contrib.auth import authenticate
from django.core.mail import send_mail
from utenti.models import Utenti
from django.conf import settings
from django.db import models
import datetime
import json
import jwt
import os

otp_code=[]

def registrati(request):
    try:
        data = json.loads(request.body.decode('utf-8'))
        required_fields = ['nome', 'email', 'password']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        utenti = Utenti.objects.filter(nome=data['nome'])
        if utenti.exists():
            return HttpResponse(status=204)
        utenti = Utenti.objects.filter(email=data['email'])
        if utenti.exists():
            return HttpResponse(status=205)

        utenti=Utenti(
            nome=data['nome'],
            email=data['email'],
            password=make_password(data['password'])
        )
        utenti.save()

        payload = {
            'user_id': utenti.id,
            'exp': datetime.datetime.utcnow() + datetime.timedelta(hours=24),
            'iat': datetime.datetime.utcnow(),
        }
        jwt_token=jwt.encode(payload, os.getenv('YWT_KEY'), algorithm='HS256')

        return JsonResponse({
			"jwttoken": f'{jwt_token}',
			"imguser": utenti.img.url,
			"nome": f'{utenti.nome}',
		},status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)

def login(request):
	try:
		data = json.loads(request.body.decode('utf-8'))
        required_fields = ['email', 'password']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

	user = authenticate(username=data["email"], password=data["password"])
	if user is not None:
		codeotp=10

		subject = 'Code OTP for access!'
		message = codeotp
		from_email = settings.EMAIL_HOST_USER
		recipient_list = [to_email]

		return JsonResponse({"tempjwt": f'{key_}' },status=200)
	else:
		return HttpResponse(status=204)

	except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)

