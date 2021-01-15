#!/bin/bash

openrc default
rc-service sshd restart
rc-service nginx restart
rc-service telagraf restart
exec top