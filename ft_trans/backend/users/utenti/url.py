from django.urls import path
from utenti.utenti import registrati

urlpatterns = [
    path('users/registrati', registrati, name='registrati'),
]