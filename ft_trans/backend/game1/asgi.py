from django.core.asgi import get_asgi_application
from channels.routing import ProtocolTypeRouter, URLRouter
from django.urls import path
from giochi import SaveGame

application = ProtocolTypeRouter({
    "http": URLRouter([
        path('g1/save_game', SaveGame.as_asgi()),
    ])
})
