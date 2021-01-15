#! /bin/sh
echo "http://dl-cdn.alpinelinux.org/alpine/edge/community/" >> /etc/apk/repositories
apk update && apk upgrade
apk --no-cache add grafana telegraf
apk add openrc --no-cache
mkdir /run/openrc
touch /run/openrc/softlevel
rc-update add telegraf default
mkdir -p /var/lib/grafana/dashboards
