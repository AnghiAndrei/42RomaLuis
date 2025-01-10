from django.urls import re_path
from giochi.giochi import SaveGame

websocket_urlpatterns = [
    path('g1/save_game', SaveGame.as_asgi()),
]