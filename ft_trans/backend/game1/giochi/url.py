from django.urls import path
from giochi.giochi import save_game

urlpatterns = [
    path('g1/save_game', save_game, name='save_game'),
]