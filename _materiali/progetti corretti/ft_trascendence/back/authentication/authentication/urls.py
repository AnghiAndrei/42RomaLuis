from django.urls import path, include
from . import views
from .views import (
    CustomMFAFirstStepJWTView,
    CustomMFASecondStepJWTView,
    CustomActivateMFAView,
)
from rest_framework_simplejwt.views import (
    TokenRefreshView,
)

urlpatterns = [
    path("oauth_42", views.oauth_42, name="oauth"),
    path("auth_42", views.auth_42, name="auth_42"),
    path("register_api", views.register_api, name="register_api"),
    path("token/refresh", TokenRefreshView.as_view(), name="token_refresh"),
    path(
        "<str:method>/activate/confirm/",
        CustomActivateMFAView.as_view(),
        name="mfa-activate-confirm",
    ),
    path("login/", CustomMFAFirstStepJWTView.as_view(), name="generate-code-jwt"),
    path(
        "login/code/", CustomMFASecondStepJWTView.as_view(), name="generate-token-jwt"
    ),
    path("", include("trench.urls")),
    path("", include("trench.urls.jwt")),
]
