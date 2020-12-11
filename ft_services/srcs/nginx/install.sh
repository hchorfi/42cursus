#!/bin/sh

apk update
mkdir /run/nginx
mkdir /www
adduser -D -g 'www' www
apk add nginx
chown -R www:www /var/lib/nginx
chown -R www:www /www
apk --no-cache add curl
apk add openrc --no-cache
mv /nginx.conf /etc/nginx
mv /nginx-selfsigned.crt /etc/ssl/certs/
mv /nginx-selfsigned.key /etc/ssl/private/
mv /index.html /www
mkdir /run/openrc
touch /run/openrc/softlevel
#-----------------------------------------
apk add openssh
mv sshd_config /etc/ssh/sshd_config
rc-update add sshd
rc-status
echo "root:root" | chpasswd