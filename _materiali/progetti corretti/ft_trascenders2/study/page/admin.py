from django.contrib import admin
from .models import ZongUser

class ZongUserAdmin(admin.ModelAdmin):
    list_display = ('username', 'online', 'email', 'isTwoFactorEnabled', 'twoFactorCompleted', 'lastCodeSent', 'lastSentTime', 'location', 'Alias', 'game_total', 'game_won')
    search_fields = ('username', 'email', 'location', 'Alias')
    list_filter = ('online', 'isTwoFactorEnabled', 'twoFactorCompleted')
    filter_horizontal = ('friends', 'block', 'matches')
    
    fieldsets = (
        (None, {
            'fields': ('username', 'online', 'email', 'isTwoFactorEnabled', 'twoFactorCompleted', 'lastCodeSent', 'lastSentTime', 'location', 'Alias', 'game_total', 'game_won', 'img')
        }),
        ('Relations', {
            'fields': ('friends', 'block', 'matches')
        }),
    )

    def save_model(self, request, obj, form, change):
        if not change:  # If this is a new object, set default values
            obj.online = False
            obj.isTwoFactorEnabled = False
            obj.twoFactorCompleted = False
            obj.game_total = 0
            obj.game_won = 0
        super().save_model(request, obj, form, change)

admin.site.register(ZongUser, ZongUserAdmin)