#!/bin/sh

apk update

apk --no-cache add curl
apk add openrc --no-cache
mkdir /run/openrc
touch /run/openrc/softlevel
openrc default
mkdir /run/nginx
mkdir /www
adduser -D -g 'www' www
chown -R www:www /var/lib/nginx
chown -R www:www /www
apk add nginx
mv /nginx.conf /etc/nginx
mv /nginx-selfsigned.crt /etc/ssl/certs/
mv /nginx-selfsigned.key /etc/ssl/private/
mv /index.html /www
rc-service nginx start
#-----------------------------------------
apk add openssh
mv sshd_config /etc/ssh/sshd_config
rc-update add sshd
rc-status
rc-service sshd start
echo "root:root" | chpasswd