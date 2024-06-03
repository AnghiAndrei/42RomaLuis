from django.urls import path
from . import views

urlpatterns = [
    path("leaderboard/", views.get_leaderboard, name="game"),
]
