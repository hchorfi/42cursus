FROM alpine
COPY install.sh /
COPY services.sh /
RUN sh install.sh
EXPOSE 3306
VOLUME [ "/sys/fs/cgroup" ]
ENTRYPOINT [ "sh", "services.sh" ]