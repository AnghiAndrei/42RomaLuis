FROM alpine:3.13
EXPOSE 443 80
COPY configure.sh configure.sh
RUN	apk update && apk upgrade && apk add --no-cache nginx && apk add openrc --no-cache
COPY nginx.conf etc/nginx/conf.d/nginx.conf