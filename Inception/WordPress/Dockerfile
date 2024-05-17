FROM debian:buster

RUN apt-get update && \
	apt-get install -y wget && \
	apt-get install -y php-fpm && \
	wget https://wordpress.org/latest.tar.gz && \
	tar -xzvf latest.tar.gz && \
	cd /var && \
	mkdir www && \
	cd /var/www && \
	mkdir html && \
	chmod 777 /var/www/html && \
	cd ../.. && \
	mv wordpress /var/www/html/wordpress && \
	cd /var/www/html/wordpress && \
	mv wp-config-sample.php wp-config.php

EXPOSE 9000