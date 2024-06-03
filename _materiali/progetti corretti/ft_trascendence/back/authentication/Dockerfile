# Dockerfile.user
FROM python:3.8

WORKDIR /usr/src/app

COPY . .

RUN apt-get update && apt-get install -y postgresql-client
RUN pip install --no-cache-dir \
    Django==3.2.8 \
    python-social-auth \
    social-auth-app-django \
    python-decouple \
    psycopg2-binary \
    python-dotenv \
    django-oauth-toolkit \
    Pillow \
    djangorestframework \
    django-cors-headers \
    django-sslserver \
    django-environ \
    djangorestframework-simplejwt \
    django-trench \
    email-validator \
    channels \
    daphne \
    channels_redis

EXPOSE 4000

ENTRYPOINT ["./entrypoint.sh"]