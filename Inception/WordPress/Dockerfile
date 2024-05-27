FROM alpine:3.19
EXPOSE 9000
COPY configure.sh configure.sh
RUN	apk update && \
	apk upgrade && \
	apk add --no-cache php81 php81-fpm php81-mysqli && \
	sed -i "s|listen = 127.0.0.1:9000|listen = 9000|g" /etc/php81/php-fpm.d/www.conf && \
    sed -i "s|;listen.owner = nobody|listen.owner = nobody|g" /etc/php81/php-fpm.d/www.conf && \
    sed -i "s|;listen.group = nobody|listen.group = nobody|g" /etc/php81/php-fpm.d/www.conf