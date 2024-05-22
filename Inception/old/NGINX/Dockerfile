FROM alpine:3
EXPOSE 443 80
COPY configure.sh configure.sh
RUN	apk update && \
	apk add --no-cache nginx openrc
COPY nginx.conf etc/nginx/conf.d/nginx.conf