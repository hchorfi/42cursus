#!/bin/bash

rc-service sshd restart
rc-service nginx restart
exec top