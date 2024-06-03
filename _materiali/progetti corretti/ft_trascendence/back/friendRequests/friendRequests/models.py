from django.db import models
from django.contrib.auth.models import AbstractUser


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


class FriendRequest(models.Model):
    sender = models.ForeignKey(
        CustomUser, related_name="sender", on_delete=models.CASCADE
    )
    receiver = models.ForeignKey(
        CustomUser, related_name="receiver", on_delete=models.CASCADE
    )
    accepted = models.BooleanField(default=False)
    date_created = models.DateTimeField(auto_now_add=True)

    class Meta:
        db_table = "friendrequest"
