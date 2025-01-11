from django.http import JsonResponse, HttpResponse
from django.db import connection
from datetime import datetime
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
        required_fields = ['nomep1', 'nomep2', 'nomep3', 'nomep4', 'esito', 'pp1', 'pp2', 'pp3', 'pp4', 'gioco']
        if not all(field in data for field in required_fields):
            return HttpResponse(status=400)

        current_date = datetime.now()
        formatted_date = current_date.strftime('%d-%m-%Y')

        with connection.cursor() as cursor:
            cursor.execute("INSERT INTO giochi_partita  (id_utente, nomep1, nomep2, nomep3, nomep4, esito, data, pp1, pp2, pp3, pp4, gioco) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)", [ id_user, data['nomep1'], data['nomep2'], data['nomep3'], data['nomep4'], data['esito'], formatted_date, data['pp1'], data['pp2'], data['pp3'], data['pp4'], data['gioco'], ])
        return HttpResponse(status=200)

    except Exception as e:
        print(f"Error: {e}")
        return HttpResponse(status=500)


def GetGames(request):
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

        partite = []
        totegame = 0
        totwin = 0
        totsco = 0
        totpar = 0
        with connection.cursor() as cursor:
            cursor.execute("SELECT * FROM giochi_partita WHERE id_utente = %s ORDER BY data DESC LIMIT 20", [id_user])
            results = cursor.fetchall()
            columns = [col[0] for col in cursor.description]
            partite = [dict(zip(columns, row)) for row in results]
            if not partite:
                return HttpResponse(status=400)
            cursor.execute("SELECT COUNT(id) FROM giochi_partita WHERE id_utente = %s AND esito = 'V'", [id_user])
            totwin = cursor.fetchone()[0]
            cursor.execute("SELECT COUNT(id) FROM giochi_partita WHERE id_utente = %s AND esito = 'S'", [id_user])
            totsco = cursor.fetchone()[0]
            cursor.execute("SELECT COUNT(id) FROM giochi_partita WHERE id_utente = %s AND esito = 'P'", [id_user])
            totpar = cursor.fetchone()[0]
            cursor.execute("SELECT COUNT(id) FROM giochi_partita WHERE id_utente = %s", [id_user])
            totegame = cursor.fetchone()[0]
        return JsonResponse({"totwin": totwin, "totsco": totsco, "totpar": totpar, "totegame": totegame, "partite": partite}, status=200)

    except Exception as e:
        print(f"Error: {e}")
        return HttpResponse(status=500)