import json
from django.http import JsonResponse, HttpResponseForbidden, HttpResponse, HttpResponseNotAllowed
from page.models import ZongUser
from chat.models import Chat

def getZongUsers(request):
	users = ZongUser.objects.exclude(username=request.user.username)
	zong_users = []
	for user in users:
		zong_users.append({
			'username': user.username,
			'alias': user.Alias,
		})
	return JsonResponse(zong_users, safe=False)

def getOnline(request):
	users = ZongUser.objects.filter(online=True).exclude(username=request.user.username)
	names = []
	for user in users:
		names.append(user.username)
	return JsonResponse({'online':names})

def add_friend(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])
	
	json_data = json.loads(request.body)
	username = json_data.get('username')
	
	user_exists = ZongUser.objects.filter(username=username).exists()
	if user_exists == False:
		return HttpResponse(f"{username} is not a user", status=400)
	
	friend = ZongUser.objects.get(username=username)
	user = ZongUser.objects.get(username=request.user.username)
	if (friend == user):
		return HttpResponse("cannot add yourself", status=400)
	if friend in user.friends.all():
		return HttpResponse("already friends", status=400)
	if friend in user.block.all():
		return HttpResponse(f"Cannot add friend: either {username} is blocked", status=400)
	if user in friend.block.all():
		return HttpResponse(f"Cannot add friend: {username} blocked you", status=400)

	user.friends.add(friend)

	try:
		user.save()
	except Exception as e:
		return HttpResponse(f"Error saving friend: {e}", status=400)
	
	return HttpResponse("Friend added")

def remove_friend(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])
	json_data = json.loads(request.body)
	username = json_data.get('username')

	user_exists = ZongUser.objects.filter(username=username).exists()
	if user_exists == False:
		return HttpResponse(f"{username} is not a user", status=400)

	friend = ZongUser.objects.get(username=username)
	user = ZongUser.objects.get(username=request.user.username)
#	if friend in user.block.all():
#		user.block.remove(friend)
#		user.save()
	if friend not in user.friends.all():
		return HttpResponse("already not friends", status=400)
	user.friends.remove(friend)
	try:
		user.save()
	except Exception as e:
		return HttpResponse("Error saving modify: {e}", status=400)
	return HttpResponse("Friend removed")

def remove_blocked(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])
	json_data = json.loads(request.body)
	username = json_data.get('username')

	user_exists = ZongUser.objects.filter(username=username).exists()
	if user_exists == False:
		return HttpResponse(f"{username} is not a user", status=400)

	friend = ZongUser.objects.get(username=username)
	user = ZongUser.objects.get(username=request.user.username)
#	if friend in user.block.all():
#		user.block.remove(friend)
#		user.save()
	if friend not in user.block.all():
		return HttpResponse("User is not blocked", status=400)
	user.block.remove(friend)
	try:
		user.save()
	except Exception as e:
		return HttpResponse(f"Error saving modify: {e}", status=400)
	return HttpResponse(f"User {username} unblocked")

def blockUser(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])
	json_data = json.loads(request.body)
	username = json_data.get('username')

	user_exists = ZongUser.objects.filter(username=username).exists()
	if user_exists == False:
		return HttpResponse(f"{username} is not a user", status=400)

	friend = ZongUser.objects.get(username=username)
	user = ZongUser.objects.get(username=request.user.username)

	if friend == user:
		return HttpResponse("Cannot block yourself", status=400)


	if friend in user.block.all():
		return HttpResponse("already blocked", status=400)
	if friend in user.friends.all():
		user.friends.remove(friend)
		friend.friends.remove(user)
		user.save()
		friend.save()
	
	chat = Chat.get_chat_by_users(user, friend)
	chat.delete()

	user.block.add(friend)
	try:
		user.save()
	except Exception as e:
		return HttpResponse(f"Error saving block: {e}", status=400)
	return HttpResponse("User blocked")
