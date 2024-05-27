#!/bin/sh
echo '<?php' > aanghi.temp
echo 'define( "DB_NAME", "'$WP_DB'" );' >> aanghi.temp
echo 'define( "DB_USER", "'$WP_DB_USR'" );' >> aanghi.temp
echo 'define( "DB_PASSWORD", "'$WP_DB_PASS'" );' >> aanghi.temp
echo 'define( "DB_HOST", "mariadb" );' >> aanghi.temp
echo 'define( "DB_CHARSET", "utf8" );' >> aanghi.temp
echo 'define( "DB_COLLATE", "" );' >> aanghi.temp
echo '$table_prefix = "wp_";' >> aanghi.temp
echo 'define( "WP_DEBUG", false );' >> aanghi.temp
echo 'if ( ! defined( "ABSPATH" ) ) {define( "ABSPATH", __DIR__ . "/" );}' >> aanghi.temp
echo 'require_once ABSPATH . "wp-settings.php";' >> aanghi.temp

if [ ! -e "/var/www/html/wordpress/wp-config.php" ]; then
	apk update && apk add --no-cache wget tar
	wget https://wordpress.org/latest.tar.gz
	tar -xzvf latest.tar.gz
	cp -r wordpress/* /var/www/html/wordpress/
	cp aanghi.temp /var/www/html/wordpress/wp-config.php
fi

# killa qualsiasi processo che si trova ad ascoltare sulla porta 9000, non consigliato da usare
# if [ ! -e "./stop.aanghi" ]; then
# 	echo il cazzo di budda > ./stop.aanghi
# 	PID=$(lsof -t -i :9000)
# 	kill -9 $PID
# fi
php-fpm81 -F