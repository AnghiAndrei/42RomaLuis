from django.contrib import admin
from .models import Message, Chat

@admin.register(Message)
class MessageAdmin(admin.ModelAdmin):
    list_display = ('sender', 'content', 'timestamp')
    search_fields = ('content', 'sender__username')
    list_filter = ('timestamp',)

@admin.register(Chat)
class ChatAdmin(admin.ModelAdmin):
    list_display = ('user1', 'user2')
    search_fields = ('user1__username', 'user2__username')
    filter_horizontal = ('messages',)

    def get_queryset(self, request):
        queryset = super().get_queryset(request)
        queryset = queryset.prefetch_related('messages')
        return queryset


