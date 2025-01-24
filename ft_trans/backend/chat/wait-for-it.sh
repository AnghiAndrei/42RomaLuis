#!/bin/bash

python manage.py makemigrations
python manage.py migrate

# python manage.py showmigrations

daphne -b 0.0.0.0 -p 8005 asgi:application