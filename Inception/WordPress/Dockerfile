FROM debian:buster
COPY configure.sh configure.sh
RUN apt-get update && \
	apt-get install -y wget && \
	apt-get install -y php-fpm && \
	wget https://wordpress.org/latest.tar.gz && \
	tar -xzvf latest.tar.gz

EXPOSE 9000