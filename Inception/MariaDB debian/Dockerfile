FROM debian:buster
RUN apt-get update -y && apt-get install mariadb-server -y
COPY 50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY configure.sh configure.sh
CMD ["/script.sh"]