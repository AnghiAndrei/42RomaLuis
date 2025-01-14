from django.urls import re_path
from giochi.giochi import set_games, get_games
from giochi.tornei import set_tornament, get_tornament

websocket_urlpatterns = [
    path('g1/set_games', set_games.as_asgi()),
    path('g1/get_games', get_games.as_asgi()),

	path('g1/set_tornament', set_tornament.as_asgi()),
    path('g1/get_tornament', get_tornament.as_asgi()),
]