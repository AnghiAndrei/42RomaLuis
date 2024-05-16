bash
echo 'CREATE DATABASE '$WP_DB';' > aanghi.temp
echo 'CREATE USER '\'$WP_DB_USR\''@'\''localhost'\'' IDENTIFIED BY '\'$WP_DB_PASS\'';' >> aanghi.temp
echo 'GRANT ALL PRIVILEGES ON '$WP_DB'.* TO '\'$WP_DB_USR\''@'\''localhost'\'';' >> aanghi.temp
echo 'FLUSH PRIVILEGES;' >> aanghi.temp
exit
mysql < aanghi.temp