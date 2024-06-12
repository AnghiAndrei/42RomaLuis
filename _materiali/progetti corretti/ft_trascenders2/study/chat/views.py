from	django.http				import JsonResponse, HttpResponseNotAllowed
from django.db.models import Q

from .models import Chat, Message
from page.models import ZongUser

from    usermanagement.utils			import checkJWTValidity, returnJwtResponse
from    usermanagement.login			import handleLogout
'''
def index_view(request):
    user = ZongUser.objects.get(username=request.user)
    requests = user.request.all()
    frnds = user.friends.all()
    public = Room.objects.all()
    return render(request, 'chat/index.html', {
        'rooms': Room.objects.all(), 'user': user, 'requests': requests, 'frnds':frnds, 'public':public,
        })

def room_view(request, room_name):
    user = ZongUser.objects.get(username=request.user)
    frnds = user.friends.all()
    room, created = Room.objects.get_or_create(name=room_name)
    print (room_name)
    room.join(user)
    messages = Message.objects.filter(room__name=room_name)
    return render(request, 'chat/room.html', {
        "room_name": room_name, 'user':user, 'messages':messages, 'frnds':frnds, 
        })

def privatroomview(request, room_name):
    user = ZongUser.objects.get(username=request.user)
    invited_user = ZongUser.objects.get(username=room_name)
    img = ''
    if invited_user.img:
        img = invited_user.img.url
    frnds = user.friends.exclude(Q(username=invited_user.username))
    public = Room.objects.all()
    private_room = privateRoom.objects.filter((Q(user1=user, user2=invited_user) | Q(user1=invited_user, user2=user))).first()
    if private_room is None:
        private_room = privateRoom.objects.create(user1=user, user2=invited_user)
        private_room.save()
        return render(request, 'chat/room.html', {
            "room_name": private_room.id, 'user':user, 'frnds':frnds, 'chat':invited_user, 'public' :public, 'img':img, 
            'public':public, 'private':True
            })
    print("l'id è: ", private_room)
    messages = Message.objects.filter(is_private=True, private_room=private_room).all()
    game = Game.objects.filter(creator=invited_user, opponent=user, is_private=True).first()
    return render(request, 'chat/room.html', {
        "room_name": private_room.id,'user':user, 'messages':messages, 'frnds':frnds, 'chat':invited_user,
         'public':public, 'img':img, 'game':game, 'private':True
        })
'''

def getUSerChat(request):

    if request.method != 'GET':
        return HttpResponseNotAllowed(['GET'])

    isJtwValid = checkJWTValidity(request, request.user.username)
    if (isJtwValid != 0):
        handleLogout(request)
        return returnJwtResponse(isJtwValid)


    user = ZongUser.objects.get(username=request.user.username)
    chats = Chat.objects.filter(Q(user1=user) | Q(user2=user))
    allchat = {}

    for chat in chats:
        messages = {}
        chat_messages = chat.messages.all()
        for message in chat_messages:
            messages[message.sender.username] = message.content 
        allchat[chat.get_other_user(user)] = message
    return JsonResponse(allchat)