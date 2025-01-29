from channels.routing import ProtocolTypeRouter, URLRouter
from django.core.asgi import get_asgi_application
from channels.auth import AuthMiddlewareStack
from livechat import ChatConsumer
from online import OnlineConsumer
from django.urls import path
import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'settings')

application = ProtocolTypeRouter({
    "http": get_asgi_application(),
    "websocket": AuthMiddlewareStack(
        URLRouter([
            path('wchat/<str:room_name>/', ChatConsumer.as_asgi()),
            path('online/<str:token>/', OnlineConsumer.as_asgi()),
        ])
    ),
})
