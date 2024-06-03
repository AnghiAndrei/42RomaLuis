#!/bin/sh

while ! mariadb -h$HOST_DB -u$WP_DB_USR -p$WP_DB_PASS $WP_DB; do
    echo -n .
done

if [ ! -e "/var/www/html/wordpress/wp-config.php" ]; then
	cp ripasso.html /var/www/html/wordpress/ripasso.html

	cd /var/www/html/wordpress/
	apk update && apk add --no-cache wget
	wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	mv wp-cli.phar /usr/bin/wp
    wp core download --allow-root
	wp config create --dbname=$WP_DB --dbuser=$WP_DB_USR --dbpass=$WP_DB_PASS --dbhost=$HOST_DB --dbcharset="utf8" --dbcollate="utf8_general_ci" --allow-root
	wp core install --url=aanghi.42.fr --title=fiorellini --admin_user=$WP_USR_A --admin_password=$WP_PAS_A --admin_email=$WP_EMAIL_A --skip-email --allow-root
    wp user create $WP_USR $WP_EMAIL --role=author --user_pass=$WP_PAS --allow-root
    wp theme install astra --activate --allow-root
	wp plugin update --all --allow-root
fi

# killa qualsiasi processo che si trova ad ascoltare sulla porta 9000, non consigliato da usare
# if [ ! -e "./stop.aanghi" ]; then
# 	echo il cazzo di budda > ./stop.aanghi
# 	PID=$(lsof -t -i :9000)
# 	kill -9 $PID
# fi
sleep 20
echo "! Wordpress ready !"
php-fpm82 -F