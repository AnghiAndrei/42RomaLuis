from django.core.asgi import get_asgi_application
from channels.routing import ProtocolTypeRouter, URLRouter
from channels.auth import AuthMiddlewareStack
from django.urls import path
from consumers import ChatConsumer
import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'settings')

application = ProtocolTypeRouter({
    "http": get_asgi_application(
		URLRouter([
            path('g1/save', ChatConsumer.as_asgi()),
        ])
	),
    "websocket": AuthMiddlewareStack(),
})
