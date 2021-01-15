#! /bin/sh
openrc default
rc-service vsftpd restart
rc-service telagraf restart
exec top