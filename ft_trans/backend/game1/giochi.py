from channels.generic.http import AsyncHttpConsumer
from django.db import connection
from datetime import datetime
from asgiref.sync import sync_to_async
import json
import jwt

class SaveGame(AsyncHttpConsumer):
    async def handle(self, body):
        try:
            data = json.loads(body.decode('utf-8'))
            token = self.scope['headers']
            jwt_token = None
            for header in token:
                if header[0] == b'authorization':
                    jwt_token = header[1].decode().split("Bearer ")[1]

            # Decode the JWT token (uncomment if needed)
            # try:
            #     decoded_token = jwt.decode(jwt_token, "tuo_segreto_JWT", algorithms=["HS256"])
            #     user_id = decoded_token['user_id']
            # except Exception as e:
            #     await self.send_response(401, b"", headers=[(b"Content-Type", b"application/json")])
            #     return
            id_user=1

            required_fields = ['nomep1', 'nomep2', 'nomep3', 'nomep4', 'esito', 'pp1', 'pp2', 'pp3', 'pp4', 'gioco']
            if not all(field in data for field in required_fields):
                await self.send_response(404, b"", headers=[(b"Content-Type", b"application/json")])
                return

            # Esegui il codice sincrono nel contesto async
            await self.save_game_to_db(data, id_user)

            await self.send_response(201, b"", headers=[(b"Content-Type", b"application/json")])

        except Exception as e:
            print(e)
            await self.send_response(500, b"", headers=[(b"Content-Type", b"application/json")])

    @sync_to_async
    def save_game_to_db(self, data, id_user):
        with connection.cursor() as cursor:
            cursor.execute("""
                INSERT INTO partite (id_utente, nomep1, nomep2, nomep3, nomep4, esito, data, pp1, pp2, pp3, pp4, gioco)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
            """, [
                id_user,
                data['nomep1'],
                data['nomep2'],
                data['nomep3'],
                data['nomep4'],
                data['esito'],
                datetime.strptime(data['data'], '%d-%m-%Y'),
                data['pp1'],
                data['pp2'],
                data['pp3'],
                data['pp4'],
                data['gioco'],
            ])
