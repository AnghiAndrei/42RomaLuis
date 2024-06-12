from    django.db   import models
from    django      import forms
from    game.models import Match

class ZongUser(models.Model):
    username = models.CharField(max_length=50, unique=True, primary_key=True)
    online = models.BooleanField(default=False)
    email = models.CharField(max_length=50, blank=True, null=True)
    isTwoFactorEnabled = models.BooleanField(default=False)
    twoFactorCompleted = models.BooleanField(default=False)
    lastCodeSent = models.IntegerField(blank=True, null=True)
    lastSentTime = models.DateTimeField(blank=True, null=True)
    location = models.CharField(max_length=50, blank=True, null=True)
    Alias = models.CharField(max_length=50, blank=True)
    game_total = models.IntegerField(default=0)
    game_won = models.IntegerField(default=0)
    img = models.ImageField(upload_to='profile_images/', blank=True, null=True)
    friends = models.ManyToManyField('self', blank=True)
    matches = models.ManyToManyField(Match, related_name='players', blank=True)
    block = models.ManyToManyField('self', blank=True, symmetrical=False)

    def __str__(self):
        return f'{self.username}'
    
class CaricaImmagineForm(forms.ModelForm):
    class Meta:
        model = ZongUser
        fields = ['img']