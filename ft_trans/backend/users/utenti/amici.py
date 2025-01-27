from utenti.models import Utenti, Amici, RiquestFriend
from django.http import JsonResponse, HttpResponse
from django.db.models import Q
from django.db import models
import redis
import json
import jwt
import os

redis_client = redis.StrictRedis(
    host=os.getenv('REDIS_HOST', 'localhost'),
    port=int(os.getenv('REDIS_PORT', 6379)),
    db=0
)

def send_request_friend(request):
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
        required_fields = ['nome_frind']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        amico = Utenti.objects.filter(nome=data['nome_frind']).first()
        if not amico:
            return HttpResponse(status=204)

        amicoceck = RiquestFriend.objects.filter(sender=amico.id).first()
        if amicoceck:
            return HttpResponse(status=207)

        amicidata=RiquestFriend(
            sender=id_user,
            to=amico.id
        )
        amicidata.save()

        return HttpResponse(status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}'}, status=500)

def accept_request_friend(request):
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
        required_fields = ['id_req_friendo']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        richiesta = RiquestFriend.objects.filter(id=data['id_req_friendo']).first()
        if not richiesta:
            return HttpResponse(status=204)

        amicidata=Amici(
            id_user_1=richiesta.sender,
            id_user_2=richiesta.to
        )
        amicidata.save()

        richiesta.delete()

        return HttpResponse(status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}'}, status=500)

def refuse_request_friend(request):
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
        required_fields = ['id_req_friendo']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        richiesta = RiquestFriend.objects.filter(id=data['id_req_friendo'])
        if not richiesta:
            return HttpResponse(status=204)

        richiesta.delete()
        return HttpResponse(status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}'}, status=500)

def remove_friend(request):
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
        required_fields = ['id_req_friendo']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        amico = Amici.objects.filter(id=data['id_req_friendo'])
        if not amico:
            return HttpResponse(status=204)
        amico.delete()

        return HttpResponse(status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}'}, status=500)

def get_friend(request):
    try:
        token = request.headers.get('Authorization')
        jwt_token = None
        if token:
            jwt_token = token.split("Bearer ")[1]
        try:
            decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
            id_user = decoded_token['user_id']
        except Exception:
            return HttpResponse(status=401)

        amici_list = []
        amici = Amici.objects.filter(Q(id_user_1=id_user) | Q(id_user_2=id_user))

        for relazione in amici:
            friend_id = relazione.id_user_2 if relazione.id_user_1 == id_user else relazione.id_user_1
            try:
                amico = Utenti.objects.get(id=friend_id)
                is_online = redis_client.sismember("online_users", friend_id)
                amici_list.append({
                    "nome": amico.nome,
                    "imgfriend": amico.img.url,
                    "idfriend": relazione.id,
                    "online": bool(is_online)
                })
            except Utenti.DoesNotExist:
                continue

        if not amici_list:
            return HttpResponse(status=400)

        return JsonResponse({"lista_amici": amici_list}, status=200)

    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)

def get_request(request):
    try:
        token = request.headers.get('Authorization')
        jwt_token = None
        if token:
            jwt_token = token.split("Bearer ")[1]
        try:
            decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
            id_user = decoded_token['user_id']
        except Exception:
            return HttpResponse(status=401)

        richieste_list = []
        amici = RiquestFriend.objects.filter(to=id_user)

        for relazione in amici:
            friend_id = relazione.sender
            try:
                amico = Utenti.objects.get(id=friend_id)
                richieste_list.append({
                    "nome": amico.nome,
                    "imgfriend": amico.img.url,
                    "idrichiesta": relazione.id
                })
            except Utenti.DoesNotExist:
                continue

        if not richieste_list:
            return HttpResponse(status=400)

        return JsonResponse({"lista_richiesta": richieste_list}, status=200)

    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)

def search_friend(request):
    try:
        token = request.headers.get('Authorization')
        if not token:
            return HttpResponse(status=401)
        jwt_token = token.split("Bearer ")[1]
        try:
            decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
            id_user = decoded_token['user_id']
        except Exception:
            return HttpResponse(status=401)

        query = request.GET.get('query', '').strip()
        if not query:
            return JsonResponse({"lista_amici": []}, status=400)

        utenti = Utenti.objects.exclude(id=id_user).filter(nome__icontains=query)

        utenti = utenti.exclude(id__in=RiquestFriend.objects.filter(sender=id_user).values_list('to', flat=True)
        ).exclude(id__in=RiquestFriend.objects.filter(to=id_user).values_list('sender', flat=True)
        ).exclude(id__in=Amici.objects.filter(id_user_1=id_user).values_list('id_user_2', flat=True)
        ).exclude(id__in=Amici.objects.filter(id_user_2=id_user).values_list('id_user_1', flat=True))

        amici_list = [{"nome": amico.nome, "imgfriend": amico.img.url} for amico in utenti]

        return JsonResponse({"lista_amici": amici_list}, status=200)

    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)

def profilefriendo(request):
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
        required_fields = ['idamico']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        amici = Amici.objects.filter(id=data['idamico']).first()
        if not amici:
            return HttpResponse(status=204)

        if amici.id_user_1 == id_user:
            user = Utenti.objects.filter(id=amici.id_user_2).first()
            if not user:
                return HttpResponse(status=204)
            is_online = redis_client.sismember("online_users", amici.id_user_2)
            return JsonResponse({"nome": user.nome, "img": user.img.url, "online": bool(is_online)},status=200)
        else:
            user = Utenti.objects.filter(id=amici.id_user_1).first()
            if not user:
                return HttpResponse(status=204)
            is_online = redis_client.sismember("online_users", amici.id_user_1)
            return JsonResponse({"nome": user.nome, "img": user.img.url, "online": bool(is_online)},status=200)

    except Exception as e:
        return JsonResponse({"error": f'{e}' },status=500)