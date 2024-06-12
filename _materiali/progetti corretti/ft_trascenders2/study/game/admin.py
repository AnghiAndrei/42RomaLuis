from django.contrib import admin
from .models import Match

class MatchAdmin(admin.ModelAdmin):
    list_display = ('id', 'winner', 'loser', 'date', 'score')
    list_filter = ('winner', 'loser', 'date')
    search_fields = ('id', 'winner__username', 'loser__username')
    ordering = ('-date',)
    fieldsets = (
        (None, {
            'fields': ('winner', 'loser')
        }),
        ('Match Details', {
            'fields': ('date', 'score'),
        }),
    )