#!/bin/bash

rc-service nginx restart
rc-service php-fpm7 restart

exec top