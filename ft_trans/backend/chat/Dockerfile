FROM python:3.11-slim

WORKDIR /app
EXPOSE 8005
COPY requirements.txt /app/
RUN pip install --no-cache-dir -r requirements.txt && \
	apt-get update && apt-get install -y dos2unix
COPY . .
RUN dos2unix ./wait-for-it.sh
RUN chmod +x ./wait-for-it.sh

CMD ["./wait-for-it.sh"]