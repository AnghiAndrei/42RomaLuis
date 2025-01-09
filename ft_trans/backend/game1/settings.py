import os

INSTALLED_APPS = [
    'channels',
]

ASGI_APPLICATION = 'asgi'

CHANNEL_LAYERS = {
    'default': {
        'BACKEND': 'channels.layers.InMemoryChannelLayer',
    },
}

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql',
        'NAME': os.environ.get('POSTGRES_NAME', 'default_name'),
        'USER': os.environ.get('POSTGRES_USER', 'default_user'),
        'PASSWORD': os.environ.get('POSTGRES_PASSWORD', 'default_password'),
        'HOST': 'postgres',
        'PORT': '5432',
    }
}
