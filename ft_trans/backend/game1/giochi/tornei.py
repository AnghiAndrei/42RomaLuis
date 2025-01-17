from django.http import JsonResponse, HttpResponse
from giochi.models import DTLocPong24
from django.db import models
from datetime import date
import json
import jwt

def set_tornament(request):
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
        id_user = 1

        data = json.loads(request.body.decode('utf-8'))
        required_fields = ['nomep1', 'nomep2', 'nomep3', 'nomep4', 'vincitore', 'esito']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        if is_empty_or_whitespace(data['nomep1']) and is_empty_or_whitespace(data['nomep2']) and is_empty_or_whitespace(data['vincitore']):
            return HttpResponse(status=400)
        if data['esito'] != 'S' and data['esito'] != 'P' and data['esito'] != 'V':
            return HttpResponse(status=400)

        current_date = date.today().strftime('%Y-%m-%d')

        torneo=DTLocPong24(
            id_utente=id_user,
            nomep1=data['nomep1'],
            nomep2=data['nomep2'],
            nomep3=data['nomep3'],
            nomep4=data['nomep4'],
            vincitore=data['vincitore'],
            esito=data['esito'],
            data=current_date
        )
        torneo.save()
        return HttpResponse(status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)

def get_tornament(request):
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
        id_user = 1

        partite = DTLocPong24.objects.filter(id_utente=id_user)
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
            "vincitore": partita.vincitore,
            "esito": partita.esito,
            "data": partita.data.isoformat(),
        } for partita in partite]

        totwin = partite.filter(esito='V').count()
        totsco = partite.filter(esito='S').count()
        totegame = partite.count()

        return JsonResponse({
            "totwin": totwin,
            "totsco": totsco,
            "totetor": totegame,
            "tornei": partite_list
        }, status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)

# ===== UTILITIS ===== #
def is_empty_or_whitespace(string):
    return not string or string.strip() == ""