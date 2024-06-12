FROM python:3.10.12-alpine

ENV PYTHONUNBUFFERED 1
ENV PYTHONDONTWRITEBYTECODE 1

WORKDIR /app/backend

COPY study/requirements.txt /app/backend/

#COPY study/waitForDb.sh /usr/local/bin/
#RUN chmod 777 /usr/local/bin/waitForDb.sh

RUN apk add --virtual .build-deps --no-cache gcc python3-dev musl-dev && \
        pip install --no-cache-dir -r requirements.txt && \
        apk --purge del .build-deps

COPY . /app/backend/

# CMD di default, può essere sovrascritto durante l'avvio del container
CMD python manage.py makemigrations; python manage.py migrate; daphne -e ssl:8443:privateKey=certificate/localhost.key:certKey=certificate/localhost.crt study.asgi:application;
