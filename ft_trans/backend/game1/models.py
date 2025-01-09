from django.db import models

class Partita(models.Model):
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
    gioco = models.CharField(max_length=10)
    tipo = models.CharField(max_length=10)

    def __str__(self):
        return f"Partita: {self.nomep1} vs {self.nomep2} - {self.esito}"
