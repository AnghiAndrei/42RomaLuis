from django.urls import path

from . import views

app_name = "twofactor"
urlpatterns = [
    path("sendMail", views.sendMail, name="sendMail"),
    path("checkCode", views.checkCode, name="checkCode"),
    path("saveMail", views.saveMail, name="saveMail"),
    path("disablewTwof", views.disable2f, name="disablewTwof"),
]