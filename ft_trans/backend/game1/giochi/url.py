from django.urls import path
from giochi.giochi import set_game,get_game
from giochi.tornei import set_tornament, get_tornament

urlpatterns = [
    path('g1/set_game', set_game, name='set_game'),
    path('g1/get_game', get_game, name='get_game'),

	path('g1/set_tornament', set_tornament, name='set_tornament'),
    path('g1/get_tornament', get_tornament, name='get_tornament'),
]