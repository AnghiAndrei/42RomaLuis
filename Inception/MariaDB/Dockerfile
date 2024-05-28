FROM alpine:3.20
COPY configure.sh configure.sh
EXPOSE 3306
RUN	apk update && \
	apk add --no-cache mariadb mariadb-client && \
	sed -i "s|skip-networking|# skip-networking|g" /etc/my.cnf.d/mariadb-server.cnf && \
	sed -i "s|.*bind-address\s*=.*|bind-address=0.0.0.0|g" /etc/my.cnf.d/mariadb-server.cnf && \
	mkdir -p /run/mysqld && \
	chown -R mysql:mysql /run/mysqld