from django.urls import path
from . import views

urlpatterns = [
    path("addFriend/<int:user_id>/", views.add_friend, name="send-request"),
    path("removeFriend/<int:user_id>/", views.remove_friend, name="remove-friend"),
    path(
        "accept-request/<int:request_id>/",
        views.accept_friend_request,
        name="accept-request",
    ),
    path(
        "reject-request/<int:request_id>/",
        views.reject_friend_request,
        name="reject-request",
    ),
    path("requests", views.get_friends_requests, name="get-friends"),
    path("block-user/<int:user_id>/", views.block_user, name="block-user"),
    path("unblock-user/<int:user_id>/", views.unblock_user, name="unblock-user"),
]
