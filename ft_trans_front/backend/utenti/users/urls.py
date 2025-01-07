from django.urls import path
from .views import UserRegisterView

urlpatterns = [
    path('registra', UserRegisterView.as_view(), name='user-register'),
]
