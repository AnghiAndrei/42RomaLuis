INSTALLED_APPS = [
    'channels',
]

ASGI_APPLICATION = 'asgi'

CHANNEL_LAYERS = {
    'default': {
        'BACKEND': 'channels.layers.InMemoryChannelLayer',
    },
}
