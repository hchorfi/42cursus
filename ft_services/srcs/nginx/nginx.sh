#!/bin/sh

apk update
apk add nginx
adduser -D -g 'www' www
mkdir /www
chown -R www:www /var/lib/nginx
chown -R www:www /www
apk add openrc --no-cache
mkdir /run/nginx
rc-service nginx start
mkdir /run/openrc
touch /run/openrc/softlevel