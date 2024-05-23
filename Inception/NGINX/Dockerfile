FROM alpine:3.20
EXPOSE 443 80
COPY configure.sh configure.sh
RUN	apk update && \
	apk add --no-cache nginx openssl && \
	mkdir -p /etc/nginx/certs/ && \
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/certs/server.key -out /etc/nginx/certs/server.crt -subj "/CN=localhost"

COPY nginx.conf /etc/nginx/nginx.conf
COPY default.conf /etc/nginx/conf.d/default.conf