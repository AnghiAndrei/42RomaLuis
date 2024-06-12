import	json, os, requests
from django.db.models import Q

from	django.http				import JsonResponse, HttpResponseNotAllowed, HttpResponse, HttpResponseNotFound
from	django.shortcuts		import redirect
from	django.core				import serializers

from	.utils			import getToken, generate_jwt_token, checkJWTValidity, returnJwtResponse, verifyPassword, verifyImage
from	.login			import handleLogin, handleRegister, handleLogout, register42
from	page.models		import ZongUser
from	chat.models		import Chat

def register(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])
	json_data = json.loads(request.body)
	username = json_data.get('username')
	password = json_data.get('password')

	if verifyPassword(password) == False:
		return HttpResponse("Password must be between 8 and 12 characters long. It must contain 1 upper case, 1 lower case and 1 number", status=400)

	res = handleRegister(request, username, password)
	if res == 1:
		return HttpResponse('Username already taken', status=409)
	elif res == 2:
		return HttpResponse('Invalid username', status=401)
	elif res == 3:
		return HttpResponse('Username must be between 4 and 10 characters long', status=401)
	
	jwt_token = generate_jwt_token(username)

	response = HttpResponse("Register successfull")
	response.set_cookie('Jwt_Token', jwt_token, httponly=True)
	return response

def authenticate(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])
	json_data = json.loads(request.body)
	username = json_data.get('username')
	password = json_data.get('password')
	res = handleLogin(request, username, password)
	if res != 0:
		return HttpResponse('Wrong username or password', status=401)
	jwt_token = generate_jwt_token(username)
	
	response = HttpResponse("Login successfull")

	response.set_cookie('Jwt_Token', jwt_token, httponly=True)
	return response

def getData(request):
	error =request.GET.get("error")
	code =request.GET.get("code")

	if error:
		return HttpResponse("Errore sconosciuto. Contatta l'amministratore del sistema.", status=500)
	else :
		url = "https://api.intra.42.fr/v2/me"
		token = getToken(code)
		if token == None:
			return HttpResponse("Auth42 ha ritornato un errore nell'acquisizione del token.", status=500)
		
		headers = {
			"Authorization": f"Bearer {token}"
		}
		response = requests.get(url, headers=headers)
		responses = response.json()
		if response.status_code == 200:
			register42(request, responses['location'], responses['login'], responses['email'], os.getenv('42_DEFAULT_PSW'), responses['image']['versions']['large'], token)
			jwt_token = generate_jwt_token(responses['login'])
			response = redirect(os.getenv('SITE_URL'))
			response.set_cookie('Jwt_Token', jwt_token, httponly=True)
			return response
		else:
			return HttpResponse("auth42 ha ritornato un errore.", status=500)

def logout(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])

	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		return returnJwtResponse(isJtwValid)

	handleLogout(request)
	return HttpResponse('Logout successful')

def changeAlias(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])

	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		handleLogout(request)
		return returnJwtResponse(isJtwValid)

	json_data = json.loads(request.body)
	newAlias = json_data.get('Alias')

	if len(newAlias) < 3 or len(newAlias) > 10:
		return HttpResponse('Alias must be between 3 and 10 characters long', status=400)

	if ZongUser.objects.filter(Alias=newAlias).exists():
		return HttpResponse('Alias already exists', status=400)

	user = ZongUser.objects.get(username=request.user.username)
	user.Alias = newAlias
	user.save()
	return HttpResponse('Alias change successful')

def getUserData(request, nomeutente):

	if request.method != 'GET':
		return HttpResponseNotAllowed(['GET'])

	if not request.user.is_authenticated:
		return HttpResponse('Unauthorized', status=401)

	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		handleLogout(request)
		return returnJwtResponse(isJtwValid)

	user = ZongUser.objects.get(username=request.user.username)
	if nomeutente != "me":
		if ZongUser.objects.filter(username=nomeutente).exists():
			other = ZongUser.objects.get(username=nomeutente)
		else:
			return HttpResponseNotFound("User not found", status=404)
		if other in user.block.all() or user in other.block.all():
			return HttpResponseNotFound("User not found", status=404)
		user = other
	
	elif user.twoFactorCompleted == False and user.isTwoFactorEnabled == True:
		return HttpResponse('Two-factor authentication code required.', status=401)

	chats = Chat.objects.filter(Q(user1=user) | Q(user2=user))
	allchat = {}

	if chats != None:
		for chat in chats:
			messages = []
			chat_messages = chat.messages.all()
			for message in chat_messages:
				messages.append({
					'user': message.sender.username,
					'content': message.content,
					'date': message.timestamp,
				})
			allchat[chat.get_other_user(user).username] = messages
	jsonBody = {
		'User':user.username,
		'Alias': user.Alias,
		'game_total':user.game_total,
		'game_won':user.game_won,
		'isTwoFactorEnabled':user.isTwoFactorEnabled,
		'email':user.email,
		'chat': allchat,
	}
	return JsonResponse(jsonBody)

def getUserFriends(request, nomeutente):

	if request.method != 'GET':
		return HttpResponseNotAllowed(['GET'])

	if not request.user.is_authenticated:
		return HttpResponse('Unauthorized', status=401)

	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		handleLogout(request)
		return returnJwtResponse(isJtwValid)

	if nomeutente == "me":
		user = ZongUser.objects.get(username=request.user.username)
	else:
		user_exists = ZongUser.objects.filter(username=nomeutente).exists()
		if user_exists == True:
			user = ZongUser.objects.get(username=nomeutente)
		elif user_exists == False:
			return HttpResponseNotFound("User not found", status=404)

	friends = user.friends.all()
	friend_details = []
	for friend in friends:
		friend_info = {
			'username': friend.username,
			'alias': friend.Alias,
			'game_total': friend.game_total,
			'game_won': friend.game_won,
			'online': friend.online,
		}
		friend_details.append(friend_info)

	jsonBody = {
		'friends':friend_details
	}
	return JsonResponse(jsonBody)

def getUserBlocked(request, nomeutente):
	if request.method != 'GET':
		return HttpResponseNotAllowed(['GET'])

	if not request.user.is_authenticated:
		return HttpResponse('Unauthorized', status=401)

	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		handleLogout(request)
		return returnJwtResponse(isJtwValid)

	if nomeutente == "me":
		user = ZongUser.objects.get(username=request.user.username)
	else:
		user_exists = ZongUser.objects.filter(username=nomeutente).exists()
		if user_exists == True:
			user = ZongUser.objects.get(username=nomeutente)
		elif user_exists == False:
			return HttpResponseNotFound("User not found", status=404)

	blocked = user.block.all()
	blocked_details = []
	for block in blocked:
		blocked_info = {
			'username': block.username,
		}
		blocked_details.append(blocked_info)

	jsonBody = {
		'blocked':blocked_details
	}

	return JsonResponse(jsonBody)

def changeImage(request):
	
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])

	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		handleLogout(request)
		return returnJwtResponse(isJtwValid)

	image_file = request.FILES['Image']

	if verifyImage(image_file) == True:
		return HttpResponse('Image must be 1400x800 at max', status=400)

	file_path = os.path.join('page/static/media/profile_images', f"{request.user.username}_profile_image.jpg")
	if os.path.exists(file_path):
		os.remove(file_path)
	user = ZongUser.objects.get(username=request.user.username)
	user.img.save(f"{user.username}_profile_image.jpg", image_file, save=True)
	user.save()
	return HttpResponse('Image change successful')

def getUsernames(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])

	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		handleLogout(request)
		return returnJwtResponse(isJtwValid)
	
	json_data = json.loads(request.body)
	userToSearch = json_data.get('search')

	users = ZongUser.objects.filter(username__icontains=userToSearch)
	usernames = [user.username for user in users]
	usersToReturn = json.dumps(usernames)

	return JsonResponse(usersToReturn, safe=False)
