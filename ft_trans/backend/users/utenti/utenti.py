from django.contrib.auth.hashers import check_password
from django.contrib.auth.hashers import make_password
from django.http import JsonResponse, HttpResponse
from django.core.mail import send_mail
from utenti.models import Utenti
from django.db import models
import datetime
import string
import random
import json
import jwt
import os

OTP_Codes={}

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

        user = Utenti.objects.get(email=data["email"])
        if not check_password(data["password"], user.password):
            return HttpResponse(status=204)

        caratteri = string.ascii_letters + string.digits
        CodiceOTP = ''.join(random.choice(caratteri) for _ in range(8))

        i=0
        while i in OTP_Codes:
            i=i+1

        OTP_Codes[i]={"otp": CodiceOTP, "iduser": user.id, "tryc": 3}

        send_mail('Code OTP for access!', CodiceOTP, os.getenv('SEND_EMAIL'), [data["email"]])

        return JsonResponse({"tempjwt": f'{i}' },status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)

def check_2fa(request):
    try:
        data = json.loads(request.body.decode('utf-8'))
        required_fields = ['codeotp', 'key']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        if OTP_Codes[data["key"]]["otp"] == data["codeotp"]:
            utenti = Utenti.objects.get(id=OTP_Codes[data["key"]]["id"])
            payload = {
                'user_id': utenti.id,
                'exp': datetime.datetime.utcnow() + datetime.timedelta(hours=24),
                'iat': datetime.datetime.utcnow(),
            }
            jwt_token=jwt.encode(payload, os.getenv('YWT_KEY'), algorithm='HS256')

            del OTP_Codes[data["key"]]

            return JsonResponse({"jwttoken": jwt_token, "imguser": utenti.img.url, },status=200)
        else:
            if OTP_Codes[data["key"]]["tryc"] == 0:
                return HttpResponse(status=204)
            else:
                OTP_Codes[data["key"]]["tryc"] -= 1

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)
