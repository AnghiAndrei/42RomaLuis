"""
URL configuration for study project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import include, path
from rest_framework import routers
from django.conf.urls.static import static
from django.conf import settings
from django.views.static import serve
from django.urls import path, re_path

from . import views
#from restframe import views

#router = routers.DefaultRouter()
#router.register(r'users', views.UserViewSet)
#router.register(r'groups', views.GroupViewSet)

urlpatterns = [
    path('', include('page.urls')),
    path('user/', include('usermanagement.urls')),
    path('game/', include('game.urls')),
    path('live/', include('chat.urls')),
    path('2f/', include('twofactor.urls')),
    path('admin/', admin.site.urls),
    path('favicon.ico', serve, {'document_root': settings.STATICFILES_DIRS[0], 'path': 'favicon.ico'}),
    re_path(r'^.*$', views.main_page),
]

if settings.DEBUG:
    urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
