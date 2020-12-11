#!/bin/sh

apk update
apk add openrc --no-cache
mkdir /run/openrc
touch /run/openrc/softlevel
openrc default
apk add mysql mysql-client
mysql_install_db --user=mysql --datadir=/var/lib/mysql
