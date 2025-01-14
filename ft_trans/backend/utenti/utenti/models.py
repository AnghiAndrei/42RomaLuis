from django.db import models

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
