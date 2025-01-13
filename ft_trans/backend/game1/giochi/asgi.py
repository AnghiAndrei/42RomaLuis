from django.urls import re_path
from giochi.giochi import save_game, get_games

websocket_urlpatterns = [
    path('g1/save_game', save_game.as_asgi()),
    path('g1/get_games', get_games.as_asgi()),
]