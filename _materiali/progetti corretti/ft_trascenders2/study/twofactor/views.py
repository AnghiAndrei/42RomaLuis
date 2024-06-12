import	random, smtplib, json

from	django.http			import HttpResponse, HttpResponseNotAllowed
from	django.core.mail	import send_mail
from    datetime			import datetime, timezone, timedelta

from	study.settings			import EMAIL_HOST_USER
from	page.models				import ZongUser
from	usermanagement.utils	import checkJWTValidity, returnJwtResponse
from	.utils					import mailCheck

def disable2f(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])
	
	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		return returnJwtResponse(isJtwValid)
	
	user = ZongUser.objects.get(username=request.user.username)
	user.isTwoFactorEnabled = False
	user.lastCodeSent = None
	user.save()
	return HttpResponse("Two factor disabled")


def saveMail(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])
	
	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		return returnJwtResponse(isJtwValid)

	user = ZongUser.objects.get(username=request.user.username)
	if user.isTwoFactorEnabled == True:
		return HttpResponse("You have to disable two factor before changing your mail", status=403)

	json_data = json.loads(request.body)
	mail = json_data.get('email')

	if mailCheck(mail) == False:
		return HttpResponse('Invalid email', status=400)

	user.email = mail
	user.save()
	
	return HttpResponse("Email successfully saved")

# Create your views here.
def sendMail(request):
	if request.method != 'GET':
		return HttpResponseNotAllowed(['GET'])
	
	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		return returnJwtResponse(isJtwValid)
	
	user = ZongUser.objects.get(username=request.user.username)

	curr_time = datetime.now(timezone.utc)
	exp_time = user.lastSentTime + timedelta(minutes=1)
	if curr_time < exp_time:
		return HttpResponse(f"You must wait {exp_time-curr_time} seconds to request another code", status=401)

	code = random.randint(100000, 999999)
	message = f"Il tuo codice di autenticazione è: {code}"
	try:
		send_mail('Zong verify code', message, EMAIL_HOST_USER, [user.email])
		user.lastCodeSent = code
		user.lastSentTime = datetime.now(timezone.utc)
		user.save()
	except smtplib.SMTPException:
		return HttpResponse("There was a problem sending the mail, Try later", status=401)
	except smtplib.SMTPTimeoutError:
		return HttpResponse("There was a problem sending the mail, Try later", status=401)
	except smtplib.SMTPSSLError:
		return HttpResponse("There was a problem sending the mail, Try later", status=401)

	return HttpResponse('Email has been sent')

def checkCode(request):
	if request.method != 'POST':
		return HttpResponseNotAllowed(['POST'])
	
	isJtwValid = checkJWTValidity(request, request.user.username)
	if (isJtwValid != 0):
		return returnJwtResponse(isJtwValid)

	json_data = json.loads(request.body)
	code = json_data.get('code')

	user = ZongUser.objects.get(username=request.user.username)

	curr_time = datetime.now(timezone.utc)
	exp_time = user.lastSentTime + timedelta(minutes=10)

	if curr_time >= exp_time:
		return HttpResponse("Code Expired, Please request another code", status=401)

	if user.lastCodeSent == int(code):
		user.twoFactorCompleted = True
		user.isTwoFactorEnabled = True
		user.save()
		return HttpResponse("Code Accepted")

	return HttpResponse("Code does not match", status=400)