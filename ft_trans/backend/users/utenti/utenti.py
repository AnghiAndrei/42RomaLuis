from django.contrib.auth.hashers import check_password
from django.contrib.auth.hashers import make_password
from django.http import JsonResponse, HttpResponse
from validate_email import validate_email
from django.core.mail import send_mail
from utenti.models import Utenti
from django.db import models
import datetime
import secrets
import string
import json
import jwt
import os

def registrati(request):
	try:
		data = json.loads(request.body.decode('utf-8'))
		required_fields = ['nome', 'email', 'password', 'sesso']
		if not all(field in data for field in required_fields):
			return HttpResponse(status=400)

		if is_empty_or_whitespace(data['nome']):
			return HttpResponse(status=400)

		if not validate_email(data["email"]):
			return HttpResponse(status=501)

		utenti = Utenti.objects.filter(nome=data['nome'])
		if utenti:
			return HttpResponse(status=204)
		utenti2 = Utenti.objects.filter(email=data['email'])
		if utenti2:
			return HttpResponse(status=205)

		utenti=Utenti(
			nome=data['nome'],
			email=data['email'],
			password=make_password(data['password']),
			sesso=data['sesso'],
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

		try:
			user = Utenti.objects.get(email=data["email"])
		except Utenti.DoesNotExist:
			return HttpResponse(status=204)
		if not check_password(data["password"], user.password):
			return HttpResponse(status=204)

		if user.fa2 == "p114":
			caratteri = string.ascii_letters + string.digits
			CodiceOTP = ''.join(secrets.choice(caratteri) for _ in range(8))

			i = secrets.randbelow(900000) + 100000
			while i in OTP_Codes:
				i = secrets.randbelow(900000) + 100000

			payload = {
				'key': str(i),
				'exp': datetime.datetime.utcnow() + datetime.timedelta(minutes=5),
				'iat': datetime.datetime.utcnow(),
			}
			jwt_token_temp=jwt.encode(payload, os.getenv('YWT_KEY'), algorithm='HS256')

			OTP_Codes[i]={"otp": CodiceOTP, "iduser": user.id, "tryc": 3}

			try:
				send_mail('Code OTP for access!', CodiceOTP, os.getenv('SEND_EMAIL'), [data["email"]])
			except Exception as e:
				return HttpResponse(status=207)

			with open('/app/utenti/otp_codes.json', 'w') as f:
				json.dump(OTP_Codes, f)

			return JsonResponse({"tempjwt": f'{jwt_token_temp}' },status=200)
		elif user.fa2 == "p113":
			payload = {
				'user_id': user.id,
				'exp': datetime.datetime.utcnow() + datetime.timedelta(hours=24),
				'iat': datetime.datetime.utcnow(),
			}
			jwt_token=jwt.encode(payload, os.getenv('YWT_KEY'), algorithm='HS256')

			return JsonResponse({
				"jwttoken": f'{jwt_token}',
				"imguser": user.img.url,
				"nome": f'{user.nome}',
			},status=201)
		else:
			return HttpResponse(status=508)

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

		try:
			decoded_token = jwt.decode(data["key"], os.getenv('YWT_KEY'), algorithms=["HS256"])
			key = decoded_token['key']
		except Exception as e:
			return HttpResponse(status=204)

		try:
			data2 = OTP_Codes[key]
		except Exception as e:
			return HttpResponse(status=205)

		if OTP_Codes[key]["otp"] == data["codeotp"]:
			utenti = Utenti.objects.filter(id=OTP_Codes[key]["iduser"]).first()
			if not utenti:
				return HttpResponse(status=204)
			payload = {
				'user_id': utenti.id,
				'exp': datetime.datetime.utcnow() + datetime.timedelta(hours=24),
				'iat': datetime.datetime.utcnow(),
			}
			jwt_token=jwt.encode(payload, os.getenv('YWT_KEY'), algorithm='HS256')

			del OTP_Codes[key]

			with open('/app/utenti/otp_codes.json', 'w') as f:
				json.dump(OTP_Codes, f)

			return JsonResponse({"jwttoken": jwt_token, "imguser": utenti.img.url, "nome": utenti.nome },status=200)
		else:
			if OTP_Codes[key]["tryc"] == 0:
				del OTP_Codes[key]
			else:
				OTP_Codes[key]["tryc"] -= 1

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

		user = Utenti.objects.filter(id=id_user).first()
		if not user:
			return HttpResponse(status=204)
		return JsonResponse({"email": user.email, "nome": user.nome, "fa2": user.fa2 },status=200)

	except Exception as e:
		return JsonResponse({"error": f'{e}' },status=500)

def update_2fa(request):
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

		user = Utenti.objects.filter(id=id_user).first()
		if not user:
			return HttpResponse(status=204)

		data = json.loads(request.body.decode('utf-8'))
		required_fields = ['fa2']
		if not all(field in data for field in required_fields):
			return HttpResponse(status=400)

		if(data['fa2'] != "p113" and data['fa2'] != "p114"):
			return HttpResponse(status=400)

		user.fa2 = data['fa2']
		user.save()
		return HttpResponse(status=200)

	except Exception as e:
		return JsonResponse({"error": f'{e}' },status=500)

def modify(request):
	try:
		if not request.body:
			return HttpResponse(status=400)

		token = request.headers.get('Authorization')
		jwt_token = None
		if token:
			jwt_token = token.split("Bearer ")[1]
		try:
			decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
			id_user = decoded_token['user_id']
		except Exception as e:
			return HttpResponse(status=401)

		user = Utenti.objects.filter(id=id_user).first()
		if not user:
			return HttpResponse(status=204)

		img = request.FILES.get('img')
		if img is not None:
			if not img.name.lower().endswith('.png'):
				return HttpResponse(status=414)
			max_file_size = 5 * 1024 * 1024
			if img.size > max_file_size:
				return HttpResponse(status=413)
			user.img = img

		nome = request.POST.get('nome')
		if nome is None:
			return HttpResponse(status=400)
		if is_empty_or_whitespace(nome):
			return HttpResponse(status=400)
		user2 = Utenti.objects.filter(nome=nome).first()
		if user2:
			if user2.id != id_user:
				return HttpResponse(status=420)
		user.nome = nome
		user.save()
		return JsonResponse({ "imguser": user.img.url },status=200)

	except Exception as e:
		return JsonResponse({"error": f'{e}'}, status=500)

# ===== UTILITIS ===== #
def is_empty_or_whitespace(string):
	return not string or string.strip() == ""