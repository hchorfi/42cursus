FROM alpine
VOLUME [ "/sys/fs/cgroup" ]
COPY install.sh /
COPY nginx.conf /
COPY index.php /
COPY services.sh /
COPY www.conf /
COPY php.ini /
COPY config.inc.php /
RUN sh install.sh
EXPOSE 5000
ENTRYPOINT [ "sh", "services.sh" ]