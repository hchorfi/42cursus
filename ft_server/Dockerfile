FROM debian:buster
# updating packages
RUN apt-get update
RUN apt upgrade -y
# installing requirements and services
RUN apt-get install wget -y
RUN apt-get install lsb-release -y
RUN apt-get install gnupg -y
## nginx
RUN apt-get install nginx -y
## php
RUN apt-get install php7.3-fpm php7.3-common php7.3-mysql php7.3-gmp php7.3-curl \
    php7.3-intl php7.3-mbstring php7.3-xmlrpc php7.3-gd php7.3-xml php7.3-cli \
    php7.3-zip php7.3-soap php7.3-imap -y
## WORDPRESS
RUN cd /tmp
RUN wget -c https://wordpress.org/latest.tar.gz
## PhpMyAdmin
RUN wget https://files.phpmyadmin.net/phpMyAdmin/4.9.0.1/phpMyAdmin-4.9.0.1-all-languages.tar.gz

# configuring services
## nginx
COPY srcs/default /etc/nginx/sites-available/default
## wordpress
RUN tar -xvzf latest.tar.gz
RUN mv wordpress/ /var/www/html/
COPY srcs/wp-config.php /var/www/html/wordpress/wp-config.php
COPY srcs/wordpress.sql /
RUN rm /var/www/html/wordpress/wp-config-sample.php
RUN chown -R www-data:www-data /var/www/html/wordpress/
RUN chmod 755 -R /var/www/html/wordpress/
## PhpMyAdmin
RUN tar xvf phpMyAdmin-4.9.0.1-all-languages.tar.gz
RUN mv phpMyAdmin-4.9.0.1-all-languages/ /usr/share/phpmyadmin
RUN chown -R www-data:www-data /usr/share/phpmyadmin
RUN cp /usr/share/phpmyadmin/config.sample.inc.php /usr/share/phpmyadmin/config.inc.php
COPY srcs/config.inc.php /usr/share/phpmyadmin/config.inc.php
RUN ln -s /usr/share/phpmyadmin /var/www/html/phpmyadmin
## MySQL
COPY srcs/mysql-config.sh /
RUN bash mysql-config.sh
## ssl
RUN mkdir /etc/nginx/ssl
RUN cd /etc/nginx/ssl
RUN openssl req \
    -newkey rsa:2048 -nodes -keyout etc/nginx/ssl/localhost.key \
    -x509 -days 365 -out etc/nginx/ssl/localhost.crt \
    -subj "/C=US/ST=New York/L=Brooklyn/O=Example Brooklyn Company/CN=examplebrooklyn.com"
## restart and chek services
COPY srcs/services.sh /
ENTRYPOINT [ "sh", "services.sh" ]
