FROM alpine
COPY install.sh /
COPY nginx.conf /
COPY index.html /
COPY nginx-selfsigned.crt /
COPY nginx-selfsigned.key /
COPY sshd_config /
COPY services.sh /
RUN sh install.sh
EXPOSE 80 443 22
VOLUME [ "/sys/fs/cgroup" ]
ENTRYPOINT [ "sh", "services.sh" ]
#CMD ["/usr/sbin/sshd","-D"]