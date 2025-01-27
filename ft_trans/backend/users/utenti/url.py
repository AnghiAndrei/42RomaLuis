from django.urls import path
from utenti.utenti import registrati,check_2fa,login,profile,modify,update_2fa
from utenti.amici import send_request_friend,accept_request_friend,refuse_request_friend,remove_friend,get_friend,get_request,profilefriendo,search_friend
from utenti.chat import salva_msg,get_message,get_status,sblockfriendo,blockfriendo

urlpatterns = [
    path('users/registrati', registrati, name='registrati'),
    path('users/check_2fa', check_2fa, name='check_2fa'),
    path('users/login', login, name='login'),
    path('users/profile', profile, name='profile'),
    path('users/modify', modify, name='modify'),
    path('users/update_2fa', update_2fa, name='update_2fa'),

    path('users/send_request_friend', send_request_friend, name='send_request_friend'),
    path('users/accept_request_friend', accept_request_friend, name='accept_request_friend'),
    path('users/refuse_request_friend', refuse_request_friend, name='refuse_request_friend'),
    path('users/remove_friend', remove_friend, name='remove_friend'),
    path('users/get_friend', get_friend, name='get_friend'),
    path('users/get_request', get_request, name='get_request'),
    path('users/search_friend', search_friend, name='search_friend'),

    path('users/profilefriendo', profilefriendo, name='profilefriendo'),

    path('chat/salva_msg', salva_msg, name='salva_msg'),
    path('chat/get_message', get_message, name='get_message'),
    path('chat/get_status', get_status, name='get_status'),
    path('chat/sblockfriendo', sblockfriendo, name='sblockfriendo'),
    path('chat/blockfriendo', blockfriendo, name='blockfriendo'),
]
