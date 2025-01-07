from django.core.asgi import get_asgi_application
from channels.routing import ProtocolTypeRouter, URLRouter
from channels.auth import AuthMiddlewareStack
from django.urls import path
from consumers import ChatConsumer
import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'settings')

application = ProtocolTypeRouter({
    "http": get_asgi_application(),
    "websocket": AuthMiddlewareStack(
        URLRouter([
            path('chat/<str:room_name>/', ChatConsumer.as_asgi()),
        ])
    ),
})
