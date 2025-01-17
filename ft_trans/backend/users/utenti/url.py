from django.urls import path
from utenti.utenti import registrati,check_2fa,login,profile,modify

urlpatterns = [
    path('users/registrati', registrati, name='registrati'),
    path('users/check_2fa', check_2fa, name='check_2fa'),
    path('users/login', login, name='login'),
    path('users/profile', profile, name='profile'),
    path('users/modify', modify, name='modify'),
]