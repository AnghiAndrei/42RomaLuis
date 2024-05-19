FROM debian:buster
COPY configure.sh configure.sh
RUN apt-get update && \ 
	apt-get install mariadb-server -y

EXPOSE 3306