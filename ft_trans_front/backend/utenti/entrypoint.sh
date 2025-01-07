#!/bin/bash

set -e

echo "Applying database migrations..."
python manage.py migrate

echo "Starting Django server..."
exec "$@"
