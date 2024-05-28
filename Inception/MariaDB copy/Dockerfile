# FROM alpine:3.20
# COPY configure.sh configure.sh
# EXPOSE 3306
# RUN	apk update && \
# 	apk add --no-cache mariadb mariadb-client
# # # 	chmod 777 /var/run/mysqld; \
# # #     { echo '[mysqld]'; \
# # #       echo 'skip-host-cache'; \
# # #       echo 'skip-name-resolve'; \
# # #       echo 'bind-address=0.0.0.0'; \
# # #     } | tee  /etc/my.cnf.d/docker.cnf; \
# # #     sed -i "s|skip-networking|skip-networking=0|g" /etc/my.cnf.d/mariadb-server.cnf
# COPY ./my.cnf /etc/my.cnf


FROM alpine:3.20
COPY configure.sh configure.sh
EXPOSE 3306
RUN apk update && \
    apk add --no-cache mariadb mariadb-client && \
	echo " \
[mysqld] \
skip-host-cache \
skip-name-resolve \
bind-address=0.0.0.0 \
log-error=/var/log/mysql/error.log \
pid-file=/var/lib/mysql/mysqld.pid" >> /etc/my.cnf.d/docker.cnf && \
    sed -i "s|skip-networking|skip-networking=0|g" /etc/my.cnf.d/mariadb-server.cnf

# FROM debian:buster
# RUN apt-get update -y && apt-get install mariadb-server -y
# COPY 50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
# COPY configure.sh configure.sh
# CMD ["/script.sh"]