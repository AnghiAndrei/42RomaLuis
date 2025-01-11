from django.urls import re_path
from giochi.giochi import SaveGame, GetGames

websocket_urlpatterns = [
    path('g1/save_game', SaveGame.as_asgi()),
    path('g1/get_games', GetGames.as_asgi()),
]