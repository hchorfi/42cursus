#!/bin/sh

apk update

apk --no-cache add curl
apk add openrc --no-cache
mkdir /run/openrc
touch /run/openrc/softlevel
mkdir /run/nginx
mkdir /www
adduser -D -g 'www' www
apk add nginx
chown -R www:www /var/lib/nginx
chown -R www:www /www
mv /nginx.conf /etc/nginx
mv /index.php /www
rc-update add nginx default
# rc-service nginx start

#--- installing php ---#

apk add php7-fpm php7-mcrypt php7-soap php7-openssl php7-gmp php7-pdo_odbc php7-json php7-dom php7-pdo php7-zip php7-mysqli php7-sqlite3 php7-apcu php7-pdo_pgsql php7-bcmath php7-gd php7-odbc php7-pdo_mysql php7-pdo_sqlite php7-gettext php7-xmlreader php7-xmlrpc php7-bz2 php7-iconv php7-pdo_dblib php7-curl php7-ctype
#set env variable
PHP_FPM_USER="www"
PHP_FPM_GROUP="www"
PHP_FPM_LISTEN_MODE="0660"
PHP_MEMORY_LIMIT="512M"
PHP_MAX_UPLOAD="50M"
PHP_MAX_FILE_UPLOAD="200"
PHP_MAX_POST="100M"
PHP_DISPLAY_ERRORS="On"
PHP_DISPLAY_STARTUP_ERRORS="On"
PHP_ERROR_REPORTING="E_COMPILE_ERROR\|E_RECOVERABLE_ERROR\|E_ERROR\|E_CORE_ERROR"
PHP_CGI_FIX_PATHINFO=0
mv www.conf /etc/php7/php-fpm.d/
mv php.ini /etc/php7/
rc-update add php-fpm default
# rc-service php-fpm7 start

#--- installing phpmyadmin ---#
cd /www
wget http://files.directadmin.com/services/all/phpMyAdmin/phpMyAdmin-5.0.2-all-languages.tar.gz
tar zxvf phpMyAdmin-5.0.2-all-languages.tar.gz
rm phpMyAdmin-5.0.2-all-languages.tar.gz
mv phpMyAdmin-5.0.2-all-languages phpmyadmin
chown -R www:www /www/phpmyadmin
mv /config.inc.php phpmyadmin
