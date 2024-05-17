FROM debian:buster
COPY configure.sh configure.sh
RUN apt-get update && \ 
	apt-get install mariadb-server -y && \
	service mysql start

EXPOSE 3306