from django.db import models

class Utenti(models.Model):
	id = models.BigAutoField(primary_key=True)
	nome = models.CharField(max_length=255)
	email = models.CharField(max_length=255)
	password = models.CharField(max_length=255)
	sesso = models.CharField(max_length=20)
	fa2 = models.CharField(max_length=10, default='p113')
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

class DPLocPong24(models.Model):
	id = models.BigAutoField(primary_key=True)
	id_utente = models.IntegerField()
	nomep1 = models.CharField(max_length=255)
	nomep2 = models.CharField(max_length=255)
	nomep3 = models.CharField(max_length=255, null=True, blank=True)
	nomep4 = models.CharField(max_length=255, null=True, blank=True)
	esito = models.CharField(max_length=50)
	data = models.DateField()
	pp1 = models.CharField(max_length=3)
	pp2 = models.CharField(max_length=3)
	pp3 = models.CharField(max_length=3)
	pp4 = models.CharField(max_length=3)

	class Meta:
		db_table = 'giochi_dplocpong24'
		managed = False