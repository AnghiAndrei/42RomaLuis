from channels.generic.websocket import AsyncWebsocketConsumer
import aiohttp
import json

class ChatConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_group_name = self.scope['url_route']['kwargs']['room_name']

        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )
        await self.accept()

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(
            self.room_group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        data = json.loads(text_data)
        required_fields = ['message','token']
        if not all(field in data for field in required_fields):
            return

        if data['message'] is None:
            return

        try:
            async with aiohttp.ClientSession() as session:
                async with session.post(
                    "http://backend-django-users:8002/chat/salva_msg",
                    json={
                        "stanza": self.room_group_name,
                        "msg": data['message'],
                        "token": data['token'],
                    },
                ) as response:
                    if response.status != 200:
                        error_data = await response.json()
                        error_message = error_data.get('error', 'Unknown error')
                        await self.send(text_data=json.dumps({
                            'type': 'error_message',
                            'error': error_message,
                        }))
        except Exception as e:
            await self.send(text_data=json.dumps({
                'type': 'error_message',
                'error': f"An error occurred: {str(e)}",
            }))

        await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type': 'chat_message',
                'message': data['message'],
            }
        )

    async def chat_message(self, event):
        message = event['message']
        await self.send(text_data=json.dumps({
            'message': message,
        }))
