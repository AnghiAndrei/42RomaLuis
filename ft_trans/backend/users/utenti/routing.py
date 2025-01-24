from django.urls import re_path
from utenti.livechat import LiveChat

websocket_urlpatterns = [
    re_path(r"chat/(?P<room_name>\w+)/$", livechat.LiveChat.as_asgi()),
]