FROM alpine:3.13
EXPOSE 9000
COPY configure.sh configure.sh
RUN	apk update && \
	apk add --no-cache php7 php7-fpm php7-bcmath php7-bz2 php7-calendard php7-ctype php7-curl php7-dom php7-exif php7-fileinfod php7-gd php7-gmagickd php7-gmp php7-iconv php7-imap php7-intl php7-json php7-mbstringd php7-mcrypt php7-memcached php7-mysqli php7-mysqlndd php7-openssld php7-pcntl php7-pdo php7-pdo_mysqld php7-pdo_pgsqld php7-pdo_sqlite php7-pgsql php7-phar php7-posix php7-sessiond php7-shmop php7-simplexmld php7-soap php7-socketsd php7-sodium php7-sqlite3d php7-sysvsemd php7-sysvshmd php7-tokenizerd php7-xml php7-xmlreaderd php7-xmlwriterd php7-xsl php7-zip php7-zlib
	# sed -i 's/^listen = 127.0.0.1:9000/listen = 0.0.0.0:9000/' /etc/php/php-fpm.d/www.conf
COPY ./php-fpm.conf /etc/php7/php-fpm.conf
RUN	adduser -S nginx &&	addgroup -S nginx
COPY conf/php-fpm.conf /etc/php7/php-fpm.conf
COPY conf/www.conf /etc/php7/php-fpm.d/www.conf
