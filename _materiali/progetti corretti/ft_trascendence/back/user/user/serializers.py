from rest_framework import serializers
from .models import CustomUser


class CustomUserSerializer(serializers.ModelSerializer):
    class Meta:
        model = CustomUser
        fields = "__all__"


class UserInfoSerializer(serializers.ModelSerializer):
    class Meta:
        model = CustomUser
        fields = [
            "id",
            "username",
            "email",
            "profile_image",
            "score",
            "date_joined",
        ]


class UserFriendsSerializer(serializers.ModelSerializer):
    is_blocked = serializers.SerializerMethodField()

    class Meta:
        model = CustomUser
        fields = [
            "id",
            "username",
            "is_blocked",
        ]

    def get_is_blocked(self, obj):
        request = self.context.get("request")
        if request and request.user:
            return obj in request.user.blocked_users.all()
        return False
