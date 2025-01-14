FROM python:3.11.5-slim-bullseye

WORKDIR /app
EXPOSE 8002
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt && \
    apt-get update && apt-get install -y libpq-dev dos2unix netcat
COPY . .
RUN dos2unix ./wait-for-it.sh
RUN chmod +x ./wait-for-it.sh

CMD ["./wait-for-it.sh"]
