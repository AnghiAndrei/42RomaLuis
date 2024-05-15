FROM debian:buster
COPY configure.sh /tmp/configure.sh
RUN apt-get update && \ 
	apt-get install mariadb-server -y && \
	service mysql start && \
	sh /tmp/configure.sh
EXPOSE 3306
CMD /usr/bin/mysqld_safe