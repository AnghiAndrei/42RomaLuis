# !/bin/sh

chmod 770 /etc/my.cnf
mkdir -p /run/mysql

mkdir -p /var/log/mysql/
touch /var/log/mysql/error.log
chmod 770 /var/log/mysql/error.log

mkdir -p /var/run/mysqld/
touch /var/run/mysqld/mysqld.sock
chmod 770 /var/run/mysqld/mysqld.sock

mkdir -p /var/lib/mysql/
chown -R mysql:mysql /var/lib/mysql
chown mysql:mysql /var/lib/mysql
chmod 777 /var/lib/mysql
touch /var/lib/mysql/aria_log_control
chown mysql:mysql /var/lib/mysql/aria_log_control
chmod 777 /var/lib/mysql/aria_log_control

mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld
chmod 777 /run/mysqld

# mkdir -p /var/run/
# touch /var/run/mysqld
# chmod 777 /var/run/mysqld

mkdir -p /auth_pam_tool_dir/auth_pam_tool
chown root:root /auth_pam_tool_dir/auth_pam_tool

loop_command() {
    /usr/bin/mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql > /tmp/null
	/usr/bin/mysqld --user=root --datadir=/var/lib/mysql
}
loop_command &
# mysqld_pid=$!
sleep 15

mysql -u root -e "CREATE DATABASE IF NOT EXISTS $WP_DB;"
mysql -u root -e "DROP DATABASE IF EXISTS test;"
mysql -u root -e "CREATE USER IF NOT EXISTS '$WP_DB_USR'@'localhost' IDENTIFIED BY '$WP_DB_PASS';"
mysql -u root -e "GRANT ALL PRIVILEGES ON $WP_DB.* TO '$WP_DB_USR'@'localhost';"
mysql -u root -e "FLUSH PRIVILEGES;"

# kill $mysqld_pid
# sleep 15
# /usr/bin/mysqld --user=root --datadir=/var/lib/mysql


# #!/bin/bash



# service mysql start 


# echo "CREATE DATABASE IF NOT EXISTS $WP_DB;" > db1.sql
# echo "CREATE USER IF NOT EXISTS '$WP_DB_USR'@'%' IDENTIFIED BY '$WP_DB_PASS' ;" >> db1.sql
# echo "GRANT ALL PRIVILEGES ON $WP_DB.* TO '$WP_DB_USR'@'%' ;" >> db1.sql
# echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '12345' ;" >> db1.sql
# echo "FLUSH PRIVILEGES;" >> db1.sql

# mysql < db1.sql

# kill $(cat /var/run/mysqld/mysqld.pid)

# mysqld