from django.urls import path
from giochi.giochi import save_game,get_games

urlpatterns = [
    path('g1/save_game', save_game, name='save_game'),
	path('g1/get_games', get_games, name='get_games'),
]