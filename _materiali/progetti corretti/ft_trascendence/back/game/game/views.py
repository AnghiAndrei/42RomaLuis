from django.shortcuts import render
from rest_framework.decorators import api_view, permission_classes
from rest_framework.response import Response

# Create your views here.


@api_view(["GET"])
def get_leaderboard(request):
    placeholder_data = [
        {"username": "user1", "wins": 5, "losses": 3},
        {"username": "user2", "wins": 7, "losses": 2},
        {"username": "user3", "wins": 2, "losses": 8},
        # Add more placeholder data as needed
    ]
    return Response(placeholder_data)
