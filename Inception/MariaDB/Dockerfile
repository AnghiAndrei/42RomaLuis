FROM alpine:3.13
COPY configure.sh configure.sh
EXPOSE 3306
RUN	apk update && \
	apk upgrade && \
	apk add --no-cache mariadb mariadb-common mariadb-client mariadb-server-utils

COPY ./my.cnf /etc/my.cnf
# COPY ./mariadb-server.cnf /etc/my.cnf.d/mariadb-server.cnf