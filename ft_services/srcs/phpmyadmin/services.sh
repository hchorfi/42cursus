#!/bin/bash

openrc default
rc-service nginx restart
rc-service php-fpm7 restart
rc-service telagraf restart
exec top