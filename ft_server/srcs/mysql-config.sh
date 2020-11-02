#!/bin/sh

# mysql config
cd /tmp
export DEBIAN_FRONTEND=noninteractive
wget http://repo.mysql.com/mysql-apt-config_0.8.13-1_all.deb
echo "mysql-apt-config mysql-apt-config/select-server select mysql-5.7" | /usr/bin/debconf-set-selections
echo "mysql-community-server mysql-community-server/root-pass password root" | debconf-set-selections
echo "mysql-community-server mysql-community-server/re-root-pass password root" | debconf-set-selections
dpkg -i mysql-apt-config*
apt update -y
apt install mysql-server -y
chown -R mysql: /var/lib/mysql
service mysql start
mysql -u root -proot -e "CREATE USER 'hchorfi'@'localhost' IDENTIFIED BY 'password';"
mysql -u root -proot -e "GRANT ALL PRIVILEGES ON *.* TO 'hchorfi'@'localhost';"
# creat wordpress database
mysql -u root -proot -e "CREATE DATABASE wordpress;"
mysql -u root -proot -e "GRANT ALL PRIVILEGES on wordpress.* TO 'hchorfi'@'localhost' IDENTIFIED BY 'password';"
# phpmyadmin config
mysql -u root -proot < /usr/share/phpmyadmin/sql/create_tables.sql
mysql -u root -proot -e "GRANT SELECT, INSERT, UPDATE, DELETE ON phpmyadmin.* TO 'pma'@'localhost' IDENTIFIED BY 'password';"
mysql -u root -proot -e "GRANT ALL PRIVILEGES ON *.* TO 'hchorfi'@'localhost' IDENTIFIED BY 'password' WITH GRANT OPTION;"
mysql -u root -proot wordpress < /wordpress.sql
mysql -u root -proot -e "FLUSH PRIVILEGES;"