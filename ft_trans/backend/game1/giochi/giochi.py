from django.http import JsonResponse, HttpResponse
from giochi.models import DPLocPong24, DPLocPongIA
from django.db import models
from datetime import date
import json
import jwt
import os

def set_game(request):
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

		data = json.loads(request.body.decode('utf-8'))
		data = sanitaiser2025(data)
		required_fields = ['nomep1', 'nomep2', 'nomep3', 'nomep4', 'esito', 'pp1', 'pp2', 'pp3', 'pp4', 'game']
		if not all(field in data for field in required_fields):
			return HttpResponse(status=400)

		if is_empty_or_whitespace(data['nomep1']) and is_empty_or_whitespace(data['nomep2']):
			return HttpResponse(status=400)
		if data['esito'] != 'S' and data['esito'] != 'P' and data['esito'] != 'V':
			return HttpResponse(status=400)

		current_date = date.today().strftime('%Y-%m-%d')

		if data['game']=='lp24':
			partite=DPLocPong24(
				id_utente=id_user,
				nomep1=data['nomep1'],
				nomep2=data['nomep2'],
				nomep3=data['nomep3'],
				nomep4=data['nomep4'],
				esito=data['esito'],
				data=current_date,
				pp1=data['pp1'],
				pp2=data['pp2'],
				pp3=data['pp3'],
				pp4=data['pp4']
			)
		elif data['game']=='lpia':
			partite=DPLocPongIA(
				id_utente=id_user,
				nomep1=data['nomep1'],
				nomep2=data['nomep2'],
				nomep3=data['nomep3'],
				nomep4=data['nomep4'],
				esito=data['esito'],
				data=current_date,
				pp1=data['pp1'],
				pp2=data['pp2'],
				pp3=data['pp3'],
				pp4=data['pp4']
			)
		else:
			return HttpResponse(status=400)
		partite.save()
		return HttpResponse(status=200)

	except Exception as e:
		return JsonResponse({"error": f'{e}' },status=500)

def get_game(request):
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

		data = json.loads(request.body.decode('utf-8'))
		required_fields = ['game']
		if not all(field in data for field in required_fields):
			return HttpResponse(status=400)

		if data['game']=='lp24':
			partite = DPLocPong24.objects.filter(id_utente=id_user)
		elif data['game']=='lpia':
			partite = DPLocPongIA.objects.filter(id_utente=id_user)
		else:
			return HttpResponse(status=400)

		partite = partite.order_by('-id')
		if not partite.exists():
			return HttpResponse(status=404)
		if partite.count() > 20:
			partite = partite[:20]

		partite_list = [{
			"nomep1": partita.nomep1,
			"nomep2": partita.nomep2,
			"nomep3": partita.nomep3,
			"nomep4": partita.nomep4,
			"esito": partita.esito,
			"data": partita.data.isoformat(),
			"pp1": partita.pp1,
			"pp2": partita.pp2,
			"pp3": partita.pp3,
			"pp4": partita.pp4,
		} for partita in partite]

		totwin = partite.filter(esito='V').count()
		totsco = partite.filter(esito='S').count()
		totpar = partite.filter(esito='P').count()
		totegame = partite.count()

		return JsonResponse({
			"totwin": totwin,
			"totsco": totsco,
			"totpar": totpar,
			"totegame": totegame,
			"partite": partite_list
		}, status=200)

	except Exception as e:
		return JsonResponse({"error": f'{e}' },status=500)

# ===== UTILITIS ===== #
def is_empty_or_whitespace(string):
	return not string or string.strip() == ""

import bleach
def sanitaiser2025(data):
    if not isinstance(data, dict):
        raise ValueError("Il parametro deve essere un dizionario")
    return {key: bleach.clean(value, tags=[], strip=True) if isinstance(value, str) else value for key, value in data.items()}