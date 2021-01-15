#! /bin/sh
echo "http://dl-cdn.alpinelinux.org/alpine/edge/community/" >> /etc/apk/repositories
apk update && apk upgrade
apk add openrc --no-cache
mkdir /run/openrc
touch /run/openrc/softlevel
apk --no-cache add influxdb telegraf
rc-update add influxdb default
rc-update add telegraf default
