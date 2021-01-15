#! /bin/sh

openrc default
rc-service telagraf restart
cd /usr/share/grafana
/usr/sbin/grafana-server web
exec top