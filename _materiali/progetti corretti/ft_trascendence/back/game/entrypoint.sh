#!/bin/bash
set -e

PYTHON_CMD="python3"

# Aspetta che il servizio PostgreSQL sia pronto
until pg_isready -U "$POSTGRES_USER" -d "$POSTGRES_DB" -p "$DB_PORT" -h "$DB_HOST"; do
  echo 'Attendo il servizio PostgreSQL...'
  sleep 1
done

# Esegue le migrazioni del database
$PYTHON_CMD manage.py makemigrations
$PYTHON_CMD manage.py migrate

# Crea un superutente se non esiste
$PYTHON_CMD manage.py shell << EOF
from django.contrib.auth import get_user_model
User = get_user_model()

if not User.objects.filter(username='$DJANGO_SUPERUSER_USERNAME').exists():
    User.objects.create_superuser('$DJANGO_SUPERUSER_USERNAME', '$DJANGO_SUPERUSER_EMAIL', '$DJANGO_SUPERUSER_PASSWORD')
EOF

# Avvia il server Django
$PYTHON_CMD manage.py runsslserver --certificate ssl/fullchain.pem --key ssl/cert-key.pem "${BASE_IP}":4000
# Avvia il tuo server
exec "$@"
