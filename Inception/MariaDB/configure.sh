#!/bin/sh
echo 'CREATE DATABASE '$WP_DB';' > aanghi.temp
echo 'CREATE USER '\'$WP_DB_USR\''@'\''localhost'\'' IDENTIFIED BY '\'$WP_DB_PASS\'';' >> aanghi.temp
echo 'GRANT ALL PRIVILEGES ON '$WP_DB'.* TO '\'$WP_DB_USR\''@'\''localhost'\'';' >> aanghi.temp
echo 'FLUSH PRIVILEGES;' >> aanghi.temp
echo 'EXIT;' >> aanghi.temp
mkdir -p /run/mysqld
mysql_install_db --basedir=/usr --datadir=/var/lib/mysql --user=mysql --rpm > /dev/null
/usr/bin/mysqld < aanghi.temp
exec /usr/bin/mysqld --user=mysql --console