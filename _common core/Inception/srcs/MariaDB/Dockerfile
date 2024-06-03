FROM alpine:3.19.1
COPY configure.sh configure.sh
EXPOSE 3306
RUN	apk update && \
	apk add --no-cache mariadb mariadb-client mariadb-server-utils && \
	sed -i "s|skip-networking|# skip-networking|g" /etc/my.cnf.d/mariadb-server.cnf && \
	sed -i "s|.*bind-address\s*=.*|bind-address=0.0.0.0|g" /etc/my.cnf.d/mariadb-server.cnf && \
	mkdir -p /run/mysqld && \
	mkdir -p /run/mysql && \
	mkdir -p /var/lib/mysql && \
	chmod 777 /var/lib/mysql && \
	chown -R root:root /run/mysqld && \
	chown -R root:root /var/lib/mysql