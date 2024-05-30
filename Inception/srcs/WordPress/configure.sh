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
	cp ripasso.html /var/www/html/wordpress/ripasso.html #static site

	#wordpress
	apk update && apk add --no-cache wget
	wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	cp wp-cli.phar /usr/bin/wp
	cd /var/www/html/wordpress/
    wp core download --allow-root 
	sleep 15
	wp config create --dbname=$WP_DB --dbuser=$WP_DB_USR --dbpass=$WP_DB_PASS --dbhost="mariadb" --allow-root 
    sleep 15
	wp core install --url="aanghi.42.fr" --title="PorcoDio!!" --admin_user=$WP_USR_A --admin_password=$WP_PAS_A --admin_email=$WP_EMAIL_A --allow-root  
    wp user create $WP_USR $WP_EMAIL --user_pass=$WP_PAS --role="editor" --porcelain --allow-root 
    wp theme install neve --activate --allow-root
	wp plugin update --all --allow-root
fi

# killa qualsiasi processo che si trova ad ascoltare sulla porta 9000, non consigliato da usare
# if [ ! -e "./stop.aanghi" ]; then
# 	echo il cazzo di budda > ./stop.aanghi
# 	PID=$(lsof -t -i :9000)
# 	kill -9 $PID
# fi
php-fpm82 -F