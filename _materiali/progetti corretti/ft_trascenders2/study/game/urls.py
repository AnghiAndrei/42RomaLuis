from django.urls import path

from . import views

app_name = "game"
urlpatterns = [
    path("showWinner", views.showWinner, name="savematch"),
    path("getMatchData", views.getMatchData, name="getMatchData"),
]