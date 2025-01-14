#!/bin/bash

HOST=postgres
PORT=5432
TIMEOUT=60
shift 2

echo "Waiting for PostgreSQL"
for i in $(seq 1 $TIMEOUT); do
    nc -z $HOST $PORT
    if [ $? -eq 0 ]; then
        echo "PostgreSQL is available"
        break
    fi
    echo "Waiting for PostgreSQL... ($i)"
    sleep 1
done
if [ $? -ne 0 ]; then
    echo "Timeout waiting for PostgreSQL."
    exit 1
fi

python manage.py makemigrations utenti
python manage.py migrate

# python manage.py showmigrations

python manage.py runserver 0.0.0.0:8002