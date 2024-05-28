#!/bin/bash
service mysql start 
echo "CREATE DATABASE IF NOT EXISTS $WP_DB;" > db1.sql
echo "CREATE USER IF NOT EXISTS '$WP_DB_USR'@'%' IDENTIFIED BY '$WP_DB_PASS' ;" >> db1.sql
echo "GRANT ALL PRIVILEGES ON $WP_DB.* TO '$WP_DB_USR'@'%' ;" >> db1.sql
echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '12345' ;" >> db1.sql
echo "FLUSH PRIVILEGES;" >> db1.sql
mysql < db1.sql
kill $(cat /var/run/mysqld/mysqld.pid)
mysqld