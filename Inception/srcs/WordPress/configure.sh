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
	apk update && apk add --no-cache wget tar curl
	wget https://wordpress.org/latest.tar.gz
	tar -xzvf latest.tar.gz
	cp -r wordpress/* /var/www/html/wordpress/
	cp aanghi.temp /var/www/html/wordpress/wp-config.php

	curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    php wp-cli.phar --info
    chmod +x wp-cli.phar
    mv wp-cli.phar /usr/local/bin/wp
    wp core download --allow-root 

    wp config create --dbname=$WP_DB --dbuser=$WP_DB_USR --dbpass=$WP_DB_PASS --dbhost=mariadb --allow-root 
    wp core install --url=aanghi.42.fr --title=PorcoDio!! --admin_user=$WP_USR_A --admin_password=$WP_PAS_A --admin_email=$WP_EMAIL_A --allow-root  
    wp user create $WP_USR $WP_EMAIL --user_pass=$WP_PAS --role=editor --porcelain --allow-root 
    wp theme install neve --activate --allow-root
	wp plugin update --all --allow-root

	#adminer
	wget https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1-mysql-en.php -O /var/www/html/wordpress/adminer.php &> /dev/null
    wget https://raw.githubusercontent.com/Niyko/Hydra-Dark-Theme-for-Adminer/master/adminer.css -O /var/www/html/wordpress/adminer.css &> /dev/null
fi

# killa qualsiasi processo che si trova ad ascoltare sulla porta 9000, non consigliato da usare
# if [ ! -e "./stop.aanghi" ]; then
# 	echo il cazzo di budda > ./stop.aanghi
# 	PID=$(lsof -t -i :9000)
# 	kill -9 $PID
# fi
php-fpm81 -F