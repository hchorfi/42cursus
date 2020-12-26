#!/bin/bash

openrc default
rc-service nginx restart
rc-service php-fpm7 restart

exec top