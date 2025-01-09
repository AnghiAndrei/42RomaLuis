FROM python:3.11.5-slim-bullseye

ENV PIP_DISABLE_PIP_VERSION_CHECK=1 \
    PYTHONDONTWRITEBYTECODE=1 \
    PYTHONUNBUFFERED=1

WORKDIR /usr/src/app

COPY ./requirements.txt ./requirements.txt

RUN apt-get update && \
    apt-get install -y --no-install-recommends default-libmysqlclient-dev gcc libpq-dev gettext && \
    pip install --no-cache-dir -r requirements.txt && \
    apt-get remove -y gcc && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

COPY . .

EXPOSE 8003

RUN python manage.py

CMD ["daphne", "-b", "0.0.0.0", "-p", "8003", "asgi:application"]
