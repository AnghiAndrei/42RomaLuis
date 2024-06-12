from django.urls import path

from . import views
from . import userm

app_name = "usermanagement"
urlpatterns = [
    path("getData", views.getData, name="data"),
    path("register", views.register, name="register"),
    path("authenticate", views.authenticate, name="auth"),
    path("logout", views.logout, name="logout"),
    path("getUserData/<str:nomeutente>", views.getUserData, name="userData"),
    path("getUserFriend/<str:nomeutente>", views.getUserFriends, name="userFriends"),
    path("getUserBlocked/<str:nomeutente>", views.getUserBlocked, name="userBlocked"),
    path("getZongUsers", userm.getZongUsers, name="allUsers"),
    path("getOnline", userm.getOnline, name="online"),
    path("updateAlias", views.changeAlias, name="aliasUpdate"),
    path("updateImage", views.changeImage, name="imageUpdate"),
    path("addFriend", userm.add_friend, name="addFriend"),
    path("removeFriend", userm.remove_friend, name="removeFriend"),
    path("getUsernames", views.getUsernames, name="getUsernames"),
    path("blockUser", userm.blockUser, name="blockUser"),
    path("removeBlocked", userm.remove_blocked, name="removeBlocked"),
]
