rc-service vsftpd status
ps_1=$?
rc-service telegraf status
ps_2=$?
ps > ps_log
grep '\[*\]' ps_log
ps_log=$?
if [ $ps_1 -eq 0 ] && [ $ps_2 -eq 0 ] && [ $ps_log -eq 1 ]; then
        exit 0;
fi
exit 1;
