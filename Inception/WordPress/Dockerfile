FROM debian:latest

RUN apt-get update \
	apt-get install wget \
	apt-get install php-fpm \
	wget https://wordpress.org/latest.tar.gz \
	tar -xzvf latest.tar.gz \
	mv wordpress/* /var/www/html/ \
	cd /var/www/html \
	mv wp-config-sample.php wp-config.php \

EXPOSE 9000
CMD ["bash"]