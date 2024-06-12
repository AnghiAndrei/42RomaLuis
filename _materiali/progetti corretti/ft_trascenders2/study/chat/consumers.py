import json

from django.db.models import Q
from asgiref.sync import async_to_sync
from channels.generic.websocket import WebsocketConsumer
from .models import Message, Chat
from page.models import ZongUser
from django.utils import timezone


class ChatConsumer(WebsocketConsumer):
    def connect(self):
        self.room_name = self.scope["url_route"]["kwargs"]["room_name"]
        self.room_group_name = "chat_%s" % self.room_name
        self.user = self.scope["user"]
        print('self.scope["user"] e: ______________________________', self.scope["user"])

        # Join room group
        async_to_sync(self.channel_layer.group_add)(
            self.room_group_name, self.channel_name
        )

        self.accept()

        async_to_sync(self.channel_layer.group_send)(
                self.room_group_name, {"type": "chat_message", "message": "connect"}
            )

    def disconnect(self, close_code):
        # Leave room group
        async_to_sync(self.channel_layer.group_discard)(
            self.room_group_name, self.channel_name
        )

    # Receive message from WebSocket
    def receive(self, text_data):
        text_data_json = json.loads(text_data)
        message = text_data_json.get("message")
        other = text_data_json.get("other")
        sender = text_data_json.get("sender")
        #print(f'le palle sudate di Fabio:{sender}\n{self.user}\n')
        try:
            sender = ZongUser.objects.get(username=sender)
            other = ZongUser.objects.get(username=other)
            block = other.block.all()
            if sender.online == False:
                async_to_sync(self.channel_layer.group_send)(
                    self.room_group_name, {"type": "chat_message", 'other':'non online', 'user':sender.username}
                )
            elif sender in block:
                async_to_sync(self.channel_layer.group_send)(
                self.room_group_name, {"type": "chat_message", 'other':'il pisellino è bloccato', 'user':sender.username}
            )
            else:
                oMessage = Message.objects.create(sender=sender, content=message, timestamp=timezone.now())
                oMessage.save()
                chat = Chat.get_chat_by_users(sender, other)
                chat.messages.add(oMessage)
                chat.save()
                async_to_sync(self.channel_layer.group_send)(
                    self.room_group_name, {"type": "chat_message", 'other':other.username, 'user':sender.username}
                )
        except Exception as e:
            print(F"ERRORE PISELLINO L'ERRORE È: {e}")

    # Receive message from room group
    def chat_message(self, event):
        user = event.get("user")
        other = event.get("other")
        print('------------------------', other, user, self.user.username)
        if self.user.username == other or self.user.username == user:
            if other == 'non online':
                self.send(text_data=json.dumps({"message": 'message'}))
            elif other == 'il pisellino è bloccato':
                self.send(text_data=json.dumps({"message": 'message'}))
            else:
                self.send(text_data=json.dumps({"message": 'mSSessage'}))
        
