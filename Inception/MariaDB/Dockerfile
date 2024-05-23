FROM alpine:3.20
COPY configure.sh configure.sh
COPY ./my.cnf /etc/my.cnf
EXPOSE 3306
RUN	apk update && \
	apk add --no-cache mariadb mariadb-client