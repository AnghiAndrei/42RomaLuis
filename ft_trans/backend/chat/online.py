from channels.generic.websocket import AsyncWebsocketConsumer
import redis
import jwt
import os

redis_client = redis.StrictRedis(
    host=os.getenv('REDIS_HOST', 'localhost'),
    port=int(os.getenv('REDIS_PORT', 6379)),
    db=0
)

class OnlineConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        try:
            jwt_token = self.scope['url_route']['kwargs']['token']
            decoded_token = jwt.decode(jwt_token, os.getenv('YWT_KEY'), algorithms=["HS256"])
            self.user_id = decoded_token['user_id']
            if self.user_id is None:
                await self.close()
                return
            redis_client.sadd("online_users", self.user_id)
            await self.accept()
        except Exception:
            await self.close()

    async def disconnect(self, close_code):
        if hasattr(self, "user_id"):
            redis_client.srem("online_users", self.user_id)
