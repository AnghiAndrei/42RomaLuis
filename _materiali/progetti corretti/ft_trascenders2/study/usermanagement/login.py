import	os

from	django.contrib.auth.models	import User
from	django.contrib.auth			import login, authenticate, logout
from	django.contrib.auth.hashers	import check_password
from    datetime					import datetime, timezone, timedelta

from	page.models		import ZongUser
from	.utils			import get_image, CheckIfUser42Exist, get_defaultImg


def register42(request, locationInfo, username, mail, password, imag, token):
	if not User.objects.filter(username=f"{username}").exists():
		new_user = User.objects.create_user(username=username, password=password)
		login(request, new_user)
		user = ZongUser(location=locationInfo, username=username, email=mail, online=True, img=imag, Alias=username)
		user.lastSentTime = datetime.now(timezone.utc) - timedelta(minutes=1)
		user.save()
		get_image(username, token)
		return 0
	else:
		user = User.objects.get(username=username)
		if not check_password(password, user.password):
			return 1

		user = authenticate(request, username=username, password=password)
		login(request, user)
		file_path = os.path.join('page/static/media/profile_images', f"{user.username}_profile_image.jpg")
		if not os.path.exists(file_path):
			get_image(username, token)
		zuser = ZongUser.objects.get(username=username)
		zuser.online = True
		zuser.lastSentTime = datetime.now(timezone.utc) - timedelta(minutes=1)
		zuser.save()
		return 0


def handleRegister(request, username, password):
	if User.objects.filter(username=username).exists():
		return 1
	if CheckIfUser42Exist(username) == True:
		return 2
	if len(username) > 10 or len(username) < 4:
		return 3
	new_user = User.objects.create_user(username=username, password=password)
	login(request, new_user)
	user = ZongUser(username=username, online=True, Alias=username)
	user.lastSentTime = datetime.now(timezone.utc) - timedelta(minutes=1)
	user.save()
	get_defaultImg(username)
	return 0

def handleLogin(request, username, password):

	if User.objects.filter(username=username).exists():

		userdb = User.objects.get(username=username)
		if check_password(password, userdb.password):
			
			userdb = authenticate(request, username=username, password=password)
			login(request, userdb)
			file_path = os.path.join('page/static/media/profile_images', f"{username}_profile_image.jpg")
			if not os.path.exists(file_path):
				get_defaultImg(username)
			zuser = ZongUser.objects.get(username=request.user.username)
			zuser.online = True
			zuser.lastSentTime = datetime.now(timezone.utc) - timedelta(minutes=1)
			zuser.save()
			return 0
		else:
			return 1
	else:
		return 2
	
def handleLogout(request):
	if not request.user.is_anonymous:
		user = ZongUser.objects.get(username=request.user)
		user.online = False
		user.twoFactorCompleted = False
		user.save()
		logout(request)