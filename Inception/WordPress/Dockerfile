FROM alpine:3.13
EXPOSE 9000
COPY configure.sh configure.sh
RUN	apk update && apk upgrade && apk add --no-cache php-fpm && apk add openrc --no-cache