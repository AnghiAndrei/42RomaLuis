from django.http import JsonResponse, HttpResponse
from giochi.models import DatiPartita
from django.db import models
from datetime import date
import json
import jwt

def save_game(request):
    try:
        token = request.headers.get('Authorization')
        jwt_token = None
        if token:
            jwt_token = token.split("Bearer ")[1]
        # try:
        #     decoded_token = jwt.decode(jwt_token, "tuo_segreto_JWT", algorithms=["HS256"])
        #     id_user = decoded_token['user_id']
        # except Exception as e:
        #     return HttpResponse(status=401)
        id_user = 1

        data = json.loads(request.body.decode('utf-8'))
        required_fields = ['nomep1', 'nomep2', 'esito', 'pp1', 'pp2', 'pp3', 'pp4', 'gioco']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        current_date = date.today().strftime('%Y-%m-%d')

        partite=DatiPartita(
            id_utente=id_user,
            nomep1=data['nomep1'],
            nomep2=data['nomep2'],
            nomep3=data.get('nomep3'),
            nomep4=data.get('nomep4'),
            esito=data['esito'],
            data=current_date,
            pp1=data['pp1'],
            pp2=data['pp2'],
            pp3=data['pp3'],
            pp4=data['pp4'],
            gioco=data['gioco']
        )
        partite.save()
        return HttpResponse(status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)

def get_games(request):
    try:
        token = request.headers.get('Authorization')
        jwt_token = None
        if token:
            jwt_token = token.split("Bearer ")[1]
        # try:
        #     decoded_token = jwt.decode(jwt_token, "tuo_segreto_JWT", algorithms=["HS256"])
        #     id_user = decoded_token['user_id']
        # except Exception as e:
        #     return HttpResponse(status=401)
        id_user = 1

        data = json.loads(request.body.decode('utf-8'))
        required_fields = ['gioco']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        partite = DatiPartita.objects.filter(id_utente=id_user).order_by('-data')
        partite = partite[:20]
        if not partite.exists():
            return JsonResponse({"error": f'{partite}' },status=500)
            return HttpResponse(status=404)

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
