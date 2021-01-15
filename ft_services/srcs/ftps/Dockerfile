FROM alpine:3.11
COPY install.sh /
COPY services.sh /
RUN sh install.sh
COPY vsftpd.conf /etc/vsftpd/
COPY telegraf.conf /etc/telegraf.conf
COPY check.sh /
EXPOSE 21 21100
ENTRYPOINT [ "sh", "services.sh" ]

