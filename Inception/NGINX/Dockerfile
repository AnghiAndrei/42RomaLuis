FROM debian:buster

RUN apt-get update && \
    apt-get install -y nginx openssl && \
	mkdir -p /etc/nginx/ssl/ && \
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.crt -subj "/C=US/ST=State/L=City/O=Organization/OU=Unit/CN=oid.ocrop"

EXPOSE 443
COPY configure.sh configure.sh
COPY nginx.conf /etc/nginx/nginx.conf
COPY default.conf /etc/nginx/conf.d/default.conf