FROM alpine:3.19
EXPOSE 9000
COPY configure.sh configure.sh

RUN	apk update && \
	apk upgrade && \
	apk add --no-cache php81 php81-fpm && \
	adduser -S nginx &&	addgroup -S nginx
COPY php-fpm.conf /etc/php81/php-fpm.conf
COPY www.conf /etc/php81/php-fpm.d/www.conf
