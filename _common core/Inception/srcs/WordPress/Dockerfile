FROM alpine:3.19.1
EXPOSE 9000
COPY configure.sh configure.sh
RUN	apk update && \
	apk upgrade && \
	apk add --no-cache mariadb-client php php-fpm php-cli php-phar php-mysqli php-mbstring php-openssl && \
	sed -i "s|listen = 127.0.0.1:9000|listen = 9000|g" /etc/php82/php-fpm.d/www.conf && \
    sed -i "s|;listen.owner = nobody|listen.owner = nobody|g" /etc/php82/php-fpm.d/www.conf && \
    sed -i "s|;listen.group = nobody|listen.group = nobody|g" /etc/php82/php-fpm.d/www.conf
COPY ripasso.html /ripasso.html