from django.db import models

class Utenti(models.Model):
    id = models.BigAutoField(primary_key=True)
    nome = models.CharField(max_length=255)
    email = models.CharField(max_length=255)
    password = models.CharField(max_length=255)
    img = models.ImageField(upload_to='img_users/', default='./img_users/_default.png')
