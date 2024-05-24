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

mkdir -p /auth_pam_tool_dir/auth_pam_tool
chown root:root /auth_pam_tool_dir/auth_pam_tool

loop_command() {
    /usr/bin/mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql > /tmp/null
	/usr/bin/mysqld --user=root --datadir=/var/lib/mysql
}
loop_command &
sleep 10

mysql -u root -e "CREATE DATABASE IF NOT EXISTS $WP_DB;"
mysql -u root -e "DROP DATABASE IF EXISTS test;"
mysql -u root -e "CREATE USER IF NOT EXISTS '$WP_DB_USR'@'localhost' IDENTIFIED BY '$WP_DB_PASS';"
mysql -u root -e "GRANT ALL PRIVILEGES ON $WP_DB.* TO '$WP_DB_USR'@'localhost';"
mysql -u root -e "FLUSH PRIVILEGES;"

/usr/bin/mysqld --user=root --datadir=/var/lib/mysql