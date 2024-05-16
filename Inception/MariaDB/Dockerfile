FROM debian:buster
COPY configure.sql /tmp/configure.sql
RUN apt-get update && \ 
	apt-get install mariadb-server -y && \
	service mysql start && \
	mariadbd --user=mysql --bootstrap > /tmp/configure.sql
EXPOSE 3306
CMD /usr/bin/mysqld_safe