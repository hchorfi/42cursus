rc-service mariadb status
ps_1=$?
rc-service telegraf status
ps_2=$?

if [ $ps_1 -eq 0 ] && [ $ps_2 -eq 0 ]; then
        exit 0;
fi
exit 1;
