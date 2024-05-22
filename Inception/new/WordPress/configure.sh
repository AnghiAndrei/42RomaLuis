#!/bin/sh
echo '<?php' > aanghi.temp
echo 'define( "DB_NAME", "'$WP_DB'" );' >> aanghi.temp
echo 'define( "DB_USER", "'$WP_DB_USR'" );' >> aanghi.temp
echo 'define( "DB_PASSWORD", "'$WP_DB_PASS'" );' >> aanghi.temp
echo 'define( "DB_HOST", "mariadb:3306" );' >> aanghi.temp
echo 'define( "DB_CHARSET", "utf8" );' >> aanghi.temp
echo 'define( "DB_COLLATE", "" );' >> aanghi.temp
echo 'define( "AUTH_KEY",         "put your unique phrase here" );' >> aanghi.temp
echo 'define( "SECURE_AUTH_KEY",  "put your unique phrase here" );' >> aanghi.temp
echo 'define( "LOGGED_IN_KEY",    "put your unique phrase here" );' >> aanghi.temp
echo 'define( "NONCE_KEY",        "put your unique phrase here" );' >> aanghi.temp
echo 'define( "AUTH_SALT",        "putA your unique phrase here" );' >> aanghi.temp
echo 'define( "SECURE_AUTH_SALT", "put your unique phrase here" );' >> aanghi.temp
echo 'define( "LOGGED_IN_SALT",   "put your unique phrase here" );' >> aanghi.temp
echo 'define( "NONCE_SALT",       "put your unique phrase here" );' >> aanghi.temp
echo '$table_prefix = "wp_";' >> aanghi.temp
echo 'define( "WP_DEBUG", false );' >> aanghi.temp
echo 'if ( ! defined( "ABSPATH" ) ) {define( "ABSPATH", __DIR__ . "/" );}' >> aanghi.temp
echo 'require_once ABSPATH . "wp-settings.php";' >> aanghi.temp

if [ ! -e "/wordpress2/wp-config.php" ]; then
	apk update && apk add --no-cache wget tar
	wget https://wordpress.org/latest.tar.gz
	tar -xzvf latest.tar.gz
	cp -r wordpress/* /wordpress2/
	cp aanghi.temp /wordpress2/wp-config.php
fi

/usr/sbin/php-fpm7 -F -R