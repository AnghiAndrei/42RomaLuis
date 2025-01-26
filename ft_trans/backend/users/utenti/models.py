from django.db import models

class Utenti(models.Model):
    id = models.BigAutoField(primary_key=True)
    nome = models.CharField(max_length=255)
    email = models.CharField(max_length=255)
    password = models.CharField(max_length=255)
    sesso = models.CharField(max_length=20)
    img = models.ImageField(upload_to='img_users/', default='./img_users/_default.png')

class RiquestFriend(models.Model):
    id = models.BigAutoField(primary_key=True)
    sender = models.IntegerField()
    to = models.IntegerField()

class Amici(models.Model):
    id = models.BigAutoField(primary_key=True)
    id_user_1 = models.IntegerField()
    id_user_2 = models.IntegerField()
    block_by = models.IntegerField(default=-1)

class Messaggi(models.Model):
    id = models.BigAutoField(primary_key=True)
    id_utente = models.IntegerField()
    messaggio = models.CharField(max_length=255)
    stanza = models.IntegerField()
