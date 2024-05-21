#!/bin/sh

chmod 770 /etc/my.cnf
mkdir -p /run/mysql

mkdir -p /var/log/mysql/
touch /var/log/mysql/error.log
chmod 770 /var/log/mysql/error.log

mkdir -p /var/run/mysqld/
touch /var/run/mysqld/mysqld.sock
chmod 770 /var/run/mysqld/mysqld.sock

mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld

mkdir -p /var/run/
touch /var/run/mysqld
chmod 777 /var/run/mysqld

/usr/bin/mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
/usr/bin/mysqld --user=root --datadir=/var/lib/mysql

mkdir -p /auth_pam_tool_dir/auth_pam_tool
chown root:root /auth_pam_tool_dir/auth_pam_tool

mysql -umysql -e "ALTER USER 'mysql'@'localhost' IDENTIFIED BY 'mysql';"
mysql -umysql -e "CREATE DATABASE IF NOT EXISTS $WP_DB;"
mysql -umysql -e "CREATE USER '$WP_DB_USR'@'localhost' IDENTIFIED BY '$WP_DB_PASS';"
mysql -umysql -e "GRANT ALL PRIVILEGES ON $WP_DB.* TO '$WP_DB_USR'@'localhost';"
mysql -umysql -e "FLUSH PRIVILEGES;"

pkill mysqld
/usr/bin/mysqld --user=mysql --datadir=/var/lib/mysql