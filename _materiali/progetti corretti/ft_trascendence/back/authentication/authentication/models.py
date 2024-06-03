from django.contrib.auth.models import AbstractUser
from django.db import models
import os

from django.conf import settings
from django.template.context_processors import static


class CustomUser(AbstractUser):
    email = models.EmailField(unique=True)
    username = models.CharField(max_length=150, unique=True)
    profile_image = models.URLField(blank=True, null=True)
    friends = models.ManyToManyField("self", blank=True)
    blocked_users = models.ManyToManyField("self", blank=True)
    score = models.IntegerField(default=0)
    external_id = models.IntegerField(null=True, unique=True)

    class Meta:
        db_table = "customuser"

    def __str__(self):
        return self.username
