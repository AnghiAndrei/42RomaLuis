from django.conf import settings
from django.conf.urls.static import static
from django.urls import path
from . import views

urlpatterns = [
    path("availables", views.available_users, name="availables"),
    path("user_friends", views.user_friends, name="user_friends"),
    path("info", views.user_info, name="info"),
    path("update-username", views.update_username, name="update-username"),
    path("update-password", views.update_password, name="update-password"),
    path("update-email", views.update_email, name="update-email"),
    path("update-image", views.update_image, name="update-image"),
    path("player_info/<int:player_id>/", views.player_info, name="player_info"),
    path("diocane", views.diocane, name="diocane"),
]

if settings.DEBUG:
    urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
