#!/bin/sh

echo > temp.txt
echo FLUSH PRIVILEGES; >> temp.txt
echo CREATE DATABASE $WP_DB; >> temp.txt
echo CREATE USER '$WP_DB_USR'@'localhost' IDENTIFIED BY '$WP_DB_PASS'; >> temp.txt
echo GRANT ALL PRIVILEGES ON $WP_DB.* TO '$WP_DB_USR'@'localhost'; >> temp.txt
echo FLUSH PRIVILEGES; >> temp.txt
mariadbd --user=mysql --bootstrap > temp.txt