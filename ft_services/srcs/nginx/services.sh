#!/bin/bash

rc-service sshd start
rc-service nginx start
exec top