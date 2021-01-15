#!/bin/sh

echo "http://dl-cdn.alpinelinux.org/alpine/edge/community/" >> /etc/apk/repositories
apk update && apk upgrade
apk add openrc --no-cache
mkdir /run/openrc
touch /run/openrc/softlevel
apk add mariadb mariadb-client
apk --no-cache add telegraf
rc-update add telegraf default
rc-update add mariadb default
mv /mariadb-server.cnf etc/my.cnf.d/mariadb-server.cnf
