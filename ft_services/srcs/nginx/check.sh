rc-service nginx status
ps_1=$?
rc-service telegraf status
ps_2=$?
rc-service sshd status
ps_3=$?

if [ $ps_1 -eq 0 ] && [ $ps_2 -eq 0 ] && [ $ps_3 -eq 0 ]; then
        exit 0;
fi
exit 1;