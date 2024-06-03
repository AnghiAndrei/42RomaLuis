from django.shortcuts import get_object_or_404
from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import IsAuthenticated
from .models import FriendRequest
from django.contrib.auth.decorators import login_required
from rest_framework.response import Response

from .models import CustomUser


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def add_friend(request, user_id):
    receiver = get_object_or_404(CustomUser, id=user_id)
    if not receiver:
        return Response({"message": "User not found"}, status=400)
    if FriendRequest.objects.filter(sender=request.user, receiver=receiver).exists():
        return Response({"message": "Friend request already sent"}, status=202)
    FriendRequest.objects.create(sender=request.user, receiver=receiver)
    return Response({"message": "Friend request sent"}, status=200)


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def remove_friend(request, user_id):
    friend = get_object_or_404(CustomUser, id=user_id)
    if not request.user.friends.filter(id=friend.id).exists():
        return Response({"message": "This user is not your friend"}, status=400)
    request.user.friends.remove(friend)
    return Response({"message": "Friend removed"}, status=200)


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def accept_friend_request(request, request_id):
    friend_request = get_object_or_404(
        FriendRequest, sender_id=request_id, receiver_id=request.user.id
    )
    if friend_request:
        request.user.friends.add(friend_request.sender)
        friend_request.delete()
    return Response({"message": "Friend request accepted"}, status=200)


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def reject_friend_request(request, request_id):
    friend_request = get_object_or_404(
        FriendRequest, sender_id=request_id, receiver_id=request.user.id
    )
    if friend_request:
        friend_request.delete()
    return Response({"message": "Friend request rejected"}, status=200)


@api_view(["GET"])
@permission_classes([IsAuthenticated])
def get_friends_requests(request):
    friend_requests = FriendRequest.objects.filter(receiver=request.user)
    return Response(
        {
            "friend_requests": [
                {
                    "username": fr.sender.username,
                    "id": fr.sender.id,
                    "profile_image": fr.sender.profile_image,
                }
                for fr in friend_requests
            ]
        },
        status=200,
    )


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def block_user(request, user_id):
    user = get_object_or_404(CustomUser, id=user_id)
    if not user:
        return Response({"message": "User not found"}, status=400)
    print(request.user.blocked_users.all())
    if user in request.user.blocked_users.all():
        return Response({"message": "User already blocked"}, status=202)
    request.user.blocked_users.add(user)
    return Response({"message": "User blocked"}, status=200)


@api_view(["POST"])
@permission_classes([IsAuthenticated])
def unblock_user(request, user_id):
    user = get_object_or_404(CustomUser, id=user_id)
    if not user:
        return Response({"message": "User not found"}, status=400)
    if user not in request.user.blocked_users.all():
        return Response({"message": "User not blocked"}, status=202)
    request.user.blocked_users.remove(user)
    return Response({"message": "User unblocked"}, status=200)
