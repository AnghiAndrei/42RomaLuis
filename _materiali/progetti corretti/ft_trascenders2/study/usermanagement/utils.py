import	requests
import	os
import  jwt

from	PIL						    import Image
from    datetime                    import datetime, timezone, timedelta
from	django.http				    import HttpResponse
from	django.core.files.base		import ContentFile

from	page.models                 import ZongUser
from	study.settings              import JWT_SECRET_KEY, JWT_ALGORITHM

def verifyImage(image):
    try:
        img = Image.open(image)
        width, height = img.size

        if width > 2 * 1024 and height > 2 * 1024:
            return True
        else:
            return False
    except:
        return True

def verifyPassword(passw):
    upperCheck = False
    lowerCheck = False
    numberCheck = False

    if len(passw) < 8:
        return False
    
    for char in passw:
        if char.isupper():
            upperCheck = True
        elif char.islower():
            lowerCheck = True
        elif char.isdigit():
            numberCheck = True

        if upperCheck and lowerCheck and numberCheck:
            break

    if upperCheck and lowerCheck and numberCheck:
        return True
    else:
        return False

def checkJWTValidity(request, us):
    token = request.COOKIES.get('Jwt_Token')
    if token == None:
        return 1
    try:
        payload = jwt.decode(token, JWT_SECRET_KEY, algorithms=JWT_ALGORITHM)
        username = payload['username']
        if username != us:
            return 2
        return 0
    
    except jwt.ExpiredSignatureError:
        return 3
    except jwt.InvalidTokenError:
        return 4

def returnJwtResponse(errCode):
    if errCode == 1 or errCode == 2 or errCode == 4:
        return HttpResponse('Invalid token', status=401)
    elif errCode == 3:
        return HttpResponse('Token Expired', status=401)


def generate_jwt_token(username):
    curr_time = datetime.now(timezone.utc)
    expiration_time = curr_time + timedelta(days=1)
    payload = {
        'exp': expiration_time,
        'username': username,
    }
    return jwt.encode(payload, JWT_SECRET_KEY, algorithm=JWT_ALGORITHM)

def get_defaultImg(un):
    user = ZongUser.objects.get(username=un)
    local_file_path = 'page/static/images/profile_image.png'
    if os.path.isfile(local_file_path):
        with open(local_file_path, 'rb') as f:
            file_content = f.read()
    user.img.save(f"{user.username}_profile_image.jpg", ContentFile(file_content), save=True)
    user.save()

def get_image(un, token):
    user = ZongUser.objects.get(username=un)
    headers = {
        "Authorization": f"Bearer {token}"
    }
    response = requests.get(user.img, headers=headers)
    if response.status_code == 200:
        file_path = os.path.join('page/static/media/profile_images', f"{user.username}_profile_image.jpg")
        if os.path.exists(file_path):
            os.remove(file_path)
        user.img.save(f"{user.username}_profile_image.jpg", ContentFile(response.content), save=True)
        user.save()
    else:
        get_defaultImg(un)

def getToken(code):
    client_id = os.getenv("42_CLIENT_ID")
    client_secret = os.getenv("42_CLIENT_SECRET")
    url = "https://api.intra.42.fr/oauth/token"
    payload = {
        "grant_type": "authorization_code",
        "client_id": client_id,
        "client_secret": client_secret,
        "code": code,
        "redirect_uri": os.getenv("42_REDIRECT_URI")
    }   
    response = requests.post(url, data=payload)
    if response.status_code == 200:
        data = response.json()
        access_token = data["access_token"]
        return access_token
    else:
        return None
    
def getDefaultToken():
    client_id = os.getenv("42_CLIENT_ID")
    client_secret = os.getenv("42_CLIENT_SECRET")
    url = "https://api.intra.42.fr/oauth/token"
    payload = {
        "grant_type": "client_credentials",
        "client_id": client_id,
        "client_secret": client_secret,
    }
    response = requests.post(url, data=payload)
    if response.status_code == 200:
        data = response.json()
        access_token = data["access_token"]
        return access_token
    else:
    	return None
    
def CheckIfUser42Exist(username):
    url = f"https://api.intra.42.fr/v2/users?filter[login]={username}"
    access_token = getDefaultToken()
    headers = {
    	"Authorization": f"Bearer {access_token}"
    }
    response = requests.get(url, headers=headers)
    responses = response.json()
    if response.status_code == 200 and responses:
        return True
    else:
        return False