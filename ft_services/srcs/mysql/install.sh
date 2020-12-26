#!/bin/sh

apk update
apk add openrc --no-cache
mkdir /run/openrc
touch /run/openrc/softlevel
openrc default
apk add mysql mysql-client
mysql_install_db --user=mysql --datadir=/var/lib/mysql
rc-service mariadb start
mysql -u root -e "CREATE USER 'hchorfi'@'localhost' IDENTIFIED BY 'hchorfi';"
mysql -u root -e "GRANT ALL PRIVILEGES ON * . * TO 'hchorfi'@'172.17.0.%' IDENTIFIED BY 'hchorfi';"
mysql -u root -e "FLUSH PRIVILEGES;"
mysql -u root -e "CREATE DATABASE wordpress;"
mysql -u root -e "CREATE USER 'wpuser'@'localhost' IDENTIFIED BY 'password';"
mysql -u root -e "GRANT ALL PRIVILEGES ON wordpress.* TO 'wpuser'@'localhost';"
mysql -u root -e "CREATE USER 'wpuser'@'172.17.0.%' IDENTIFIED BY 'password';"
mysql -u root -e "GRANT ALL PRIVILEGES ON wordpress.* TO 'wpuser'@'172.17.0.%';"
mysql -u root -e "FLUSH PRIVILEGES;"

