import os

DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'
SECRET_KEY = os.getenv('DJANGO_KEY')
ROOT_URLCONF = 'giochi.url'

INSTALLED_APPS = [
    'channels',
    'giochi',
]

CHANNEL_LAYERS = {
    'default': {
        'BACKEND': 'channels.layers.InMemoryChannelLayer',
    },
}

ALLOWED_HOSTS = [
    'localhost',
]

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql',
        'NAME': os.getenv('POSTGRES_DB'),
        'USER': os.getenv('POSTGRES_USER'),
        'PASSWORD': os.getenv('POSTGRES_PASSWORD'),
        'HOST': 'postgres',
        'PORT': '5432',
    }
}

# DEBUG = True
# LOGGING = {
#     'version': 1,
#     'disable_existing_loggers': False,
#     'handlers': {
#         'console': {
#             'level': 'DEBUG',
#             'class': 'logging.StreamHandler',
#         },
#     },
#     'loggers': {
#         'django': {
#             'handlers': ['console'],
#             'level': 'DEBUG',
#             'propagate': True,
#         },
#     },
# }