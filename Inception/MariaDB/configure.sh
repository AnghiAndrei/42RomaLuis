# !/bin/sh
chown -R root:root /var/lib/mysql
mysql_install_db --basedir=/usr --datadir=/var/lib/mysql --user=mysql --rpm > null.aanghi
/usr/bin/mysqld --user=root --datadir=/var/lib/mysql &
pid=$!;
sleep 15
mysql -u root -e "CREATE DATABASE IF NOT EXISTS $WP_DB;"
mysql -u root -e "DROP DATABASE IF EXISTS test;"
mysql -u root -e "CREATE USER IF NOT EXISTS '$WP_DB_USR'@'localhost' IDENTIFIED BY '$WP_DB_PASS';"
mysql -u root -e "GRANT ALL PRIVILEGES ON $WP_DB.* TO '$WP_DB_USR'@'localhost';"
mysql -u root -e "FLUSH PRIVILEGES;"
kill $pid
sleep 15
/usr/bin/mysqld --user=root --datadir=/var/lib/mysql