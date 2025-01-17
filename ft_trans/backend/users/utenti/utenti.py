from django.contrib.auth.hashers import check_password
from django.contrib.auth.hashers import make_password
from django.http import JsonResponse, HttpResponse
from validate_email import validate_email
from django.core.mail import send_mail
from utenti.models import Utenti
from django.db import models
import datetime
import string
import random
import json
import jwt
import os

def registrati(request):
    try:
        data = json.loads(request.body.decode('utf-8'))
        required_fields = ['nome', 'email', 'password']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        if is_empty_or_whitespace(data['nome']):
            return HttpResponse(status=400)

        if not validate_email(data["email"]):
            return HttpResponse(status=401)

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
        OTP_Codes={}
        try:
            with open('/app/utenti/otp_codes.json', 'r') as f:
                OTP_Codes = json.load(f)
        except Exception as e:
            print("voglio mangiare il tuo pancreas")

        data = json.loads(request.body.decode('utf-8'))
        required_fields = ['email', 'password']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        if not validate_email(data["email"]):
            return HttpResponse(status=501)

        user = Utenti.objects.filter(email=data["email"])
        if user.exists():
            return HttpResponse(status=204)
        if not check_password(data["password"], user.password):
            return HttpResponse(status=204)

        caratteri = string.ascii_letters + string.digits
        CodiceOTP = ''.join(random.choice(caratteri) for _ in range(8))

        i = random.randint(100000, 999999)
        while i in OTP_Codes:
            i = random.randint(100000, 999999)

        OTP_Codes[i]={"otp": CodiceOTP, "iduser": user.id, "tryc": 3}

        send_mail('Code OTP for access!', CodiceOTP, os.getenv('SEND_EMAIL'), [data["email"]])

        with open('/app/utenti/otp_codes.json', 'w') as f:
            json.dump(OTP_Codes, f)

        return JsonResponse({"tempjwt": f'{i}' },status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)

def check_2fa(request):
    try:
        OTP_Codes={}
        try:
            with open('/app/utenti/otp_codes.json', 'r') as f:
                OTP_Codes = json.load(f)
        except Exception as e:
            print("voglio mangiare il tuo pancreas")

        data = json.loads(request.body.decode('utf-8'))
        required_fields = ['codeotp', 'key']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        if data["key"] not in OTP_Codes:
            return HttpResponse(status=205)

        if OTP_Codes[data["key"]]["otp"] == data["codeotp"]:
            utenti = Utenti.objects.get(id=OTP_Codes[data["key"]]["iduser"])
            payload = {
                'user_id': utenti.id,
                'exp': datetime.datetime.utcnow() + datetime.timedelta(hours=24),
                'iat': datetime.datetime.utcnow(),
            }
            jwt_token=jwt.encode(payload, os.getenv('YWT_KEY'), algorithm='HS256')

            del OTP_Codes[data["key"]]

            with open('/app/utenti/otp_codes.json', 'w') as f:
                json.dump(OTP_Codes, f)

            return JsonResponse({"jwttoken": jwt_token, "imguser": utenti.img.url, "nome": utenti.nome },status=200)
        else:
            if OTP_Codes[data["key"]]["tryc"] == 0:
                del OTP_Codes[data["key"]]
            else:
                OTP_Codes[data["key"]]["tryc"] -= 1
            
            with open('/app/utenti/otp_codes.json', 'w') as f:
                json.dump(OTP_Codes, f)

            return HttpResponse(status=204)

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)

def profile(request):
    try:
        token = request.headers.get('Authorization')
        jwt_token = None
        if token:
            jwt_token = token.split("Bearer ")[1]
        try:
            decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
            id_user = decoded_token['user_id']
        except Exception as e:
            return HttpResponse(status=401)

        utenti = Utenti.objects.get(id=id_user)
        return JsonResponse({"email": utenti.email, "nome": utenti.nome },status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)

def modify(request):
    try:
        # Controlla che il corpo della richiesta non sia vuoto
        if not request.body:
            return JsonResponse({"error": "Request body is empty"}, status=400)

        # Tenta di decodificare il JSON
        try:
            data = json.loads(request.body.decode('utf-8'))
        except json.JSONDecodeError:
            return JsonResponse({"error": "Invalid JSON format"}, status=400)

        required_fields = ['nome']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        if is_empty_or_whitespace(data['nome']):
            return HttpResponse(status=400)

        img = request.FILES.get('img')

        token = request.headers.get('Authorization')
        jwt_token = None
        if token:
            jwt_token = token.split("Bearer ")[1]
        try:
            decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
            id_user = decoded_token['user_id']
        except Exception as e:
            return HttpResponse(status=401)

        utente = Utenti.objects.get(id=id_user)
        if img is not None:
            max_file_size = 5 * 1024 * 1024
            if img.size > max_file_size or not img.name.lower().endswith('.png'):
                return HttpResponse(status=400)
            utente.img = img
        utente.nome = data['nome']
        utente.save()
        return HttpResponse(status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}'}, status=500)


# ===== UTILITIS ===== #
def is_empty_or_whitespace(string):
    return not string or string.strip() == ""