# !/bin/sh
/usr/bin/mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
/usr/bin/mysqld --user=root --datadir=/var/lib/mysql &
pid=$!;
sleep 15
mysql -u root -e "CREATE DATABASE IF NOT EXISTS $WP_DB;"
mysql -u root -e "DROP DATABASE IF EXISTS test;"
mysql -u root -e "CREATE USER IF NOT EXISTS '$WP_DB_USR'@'%' IDENTIFIED BY '$WP_DB_PASS';"
mysql -u root -e "GRANT ALL PRIVILEGES ON $WP_DB.* TO '$WP_DB_USR'@'%';"
mysql -u root -e "FLUSH PRIVILEGES;"
kill $pid
exec /usr/bin/mysqld --user=root --datadir=/var/lib/mysql