from django.contrib.auth.models import User
from django.db import models
from page.models import ZongUser
from django.utils import timezone
from django.db.models import Q
from django.db.models.signals import post_delete
from django.dispatch import receiver


class Message(models.Model):
    sender = models.ForeignKey(to=ZongUser, related_name='sender', on_delete=models.CASCADE)
    content = models.CharField(max_length=512)
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        formatted_timestamp = self.timestamp.strftime('%b %d, %Y %H:%M')
        return f'{self.content} [{formatted_timestamp}]'
    
class Chat(models.Model):
    user1 = models.ForeignKey(to=ZongUser, related_name='u1', on_delete=models.CASCADE)
    user2 = models.ForeignKey(to=ZongUser, related_name='u2', on_delete=models.CASCADE)
    messages = models.ManyToManyField(to=Message, related_name='chats')

    def get_other_user(self, user):
        if self.user1 == user:
            return self.user2
        elif self.user2 == user:
            return self.user1
        
    @staticmethod
    def get_chat_by_users(user1, user2):
        try:
            chat = Chat.objects.get(Q(user1=user1, user2=user2) | Q(user1=user2, user2=user1))
        except Chat.DoesNotExist:
            chat = Chat(user1=user1, user2=user2)  # O crea con user1 e user2 come desideri
            chat.save()
        return chat

@receiver(post_delete, sender=Chat)
def delete_messages_on_chat_delete(sender, instance, **kwargs):
    # Elimina tutti i messaggi associati a questa chat
    instance.messages.all().delete()