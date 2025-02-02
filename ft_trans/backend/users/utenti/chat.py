from django.http import JsonResponse, HttpResponse
from utenti.models import Messaggi,Utenti,Amici
import json
import jwt
import os

def get_message(request):
    try:
        data = json.loads(request.body.decode('utf-8'))
        data = sanitaiser2025(data)
        required_fields = ['stanza']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=401)

        messaggio = []
        utenti = Messaggi.objects.filter(stanza=data['stanza'])
        for msg in utenti:
            friend_id = msg.id_utente
            try:
                amico = Utenti.objects.get(id=friend_id)
                messaggio.append({
                    "msg": msg.messaggio,
                    "nome": amico.nome,
                    "imgfriend": amico.img.url,
                })
            except Utenti.DoesNotExist:
                continue

        if not messaggio:
            return HttpResponse(status=400)

        return JsonResponse({"messaggio": messaggio}, status=200)

    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)

def salva_msg(request):
    try:
        data = json.loads(request.body.decode('utf-8'))
        data = sanitaiser2025(data)
        required_fields = ['stanza', 'token', 'msg']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        try:
            decoded_token = jwt.decode(data['token'], os.getenv('YWT_KEY'), algorithms=["HS256"])
            id_user = decoded_token['user_id']
        except Exception as e:
            return HttpResponse(status=401)

        utenti = Amici.objects.filter(id=data['stanza']).first()
        if utenti.block_by != -1:
            return HttpResponse(status=200)

        messaggio = Messaggi(
            messaggio = data['msg'],
            stanza = data['stanza'],
            id_utente = id_user,
        )
        messaggio.save()
        return JsonResponse({"messaggio": messaggio}, status=200)

    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)

def get_status(request):
    try:
        data = json.loads(request.body.decode('utf-8'))
        data = sanitaiser2025(data)
        required_fields = ['stanza']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        token = request.headers.get('Authorization')
        jwt_token = None
        if token:
            jwt_token = token.split("Bearer ")[1]
        try:
            decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
            id_user = decoded_token['user_id']
        except Exception:
            return HttpResponse(status=401)

        utenti = Amici.objects.filter(id=data['stanza']).first()
        if not utenti:
            return HttpResponse(status=404)

        if utenti.block_by == id_user:
            return HttpResponse(status=200)

        return HttpResponse(status=201)

    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)

def sblockfriendo(request):
    try:
        data = json.loads(request.body.decode('utf-8'))
        data = sanitaiser2025(data)
        required_fields = ['stanza']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        token = request.headers.get('Authorization')
        jwt_token = None
        if token:
            jwt_token = token.split("Bearer ")[1]
        try:
            decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
            id_user = decoded_token['user_id']
        except Exception:
            return HttpResponse(status=401)

        utenti = Amici.objects.filter(id=data['stanza']).first()
        if not utenti:
            return HttpResponse(status=404)

        if utenti.block_by == id_user:
            utenti.block_by = -1
            utenti.save()
            return HttpResponse(status=200)

        return HttpResponse(status=201)

    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)

def blockfriendo(request):
    try:
        data = json.loads(request.body.decode('utf-8'))
        data = sanitaiser2025(data)
        required_fields = ['stanza']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        token = request.headers.get('Authorization')
        jwt_token = None
        if token:
            jwt_token = token.split("Bearer ")[1]
        try:
            decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
            id_user = decoded_token['user_id']
        except Exception:
            return HttpResponse(status=401)

        utenti = Amici.objects.filter(id=data['stanza']).first()
        if not utenti:
            return HttpResponse(status=404)

        if utenti.block_by == -1:
            utenti.block_by = id_user
            utenti.save()
            return HttpResponse(status=200)
        
        return HttpResponse(status=201)

    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)

# ===== UTILITIS ===== #
import bleach
def sanitaiser2025(data):
    if not isinstance(data, dict):
        raise ValueError("Il parametro deve essere un dizionario")
    return {key: bleach.clean(value, tags=[], strip=True) if isinstance(value, str) else value for key, value in data.items()}