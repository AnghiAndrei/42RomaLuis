from django.urls import path

from . import views

urlpatterns = [
    #path('', views.index_view, name='messages'),
#    path('roomexist', views.roomexist, name='roomexist'),
    #path('private_room/<str:room_name>/', views.privatroomview, name='privatroomview'),
    #path('<str:room_name>/', views.room_view, name='chat-room'),
    path('getUserChat/', views.getUSerChat, name='getUSerChat'),
]