from django.db import models
from django.dispatch import receiver
from django.db.models.signals import post_save

class Match(models.Model):
    id = models.AutoField(primary_key=True)
    loser = models.CharField(null=True, blank=False)
    winner = models.CharField(null=True, blank=False)
    date = models.DateTimeField(auto_now_add=True, verbose_name="Date of the match")
    score = models.CharField(max_length=10, default='0:0')

    def __str__(self):
        #return f'p1:{self.p1} VS p2:{self.p2}, id:{self.id}, score:{self.score}, winner:{self.winner}, data:{self.date}'
        return f'id: {self.id}, Winner: {self.winner}'
    

