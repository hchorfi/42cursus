FROM alpine:3.11
COPY install.sh /
COPY services.sh /
RUN sh install.sh
COPY telegraf.conf /etc/telegraf.conf
COPY grafana.ini /etc/grafana.ini
COPY dash-config.yaml /usr/share/grafana/conf/provisioning/dashboards
ADD dashboards /var/lib/grafana/dashboards
ADD datasources /usr/share/grafana/conf/provisioning/datasources
COPY check.sh /
EXPOSE 3000
ENTRYPOINT [ "sh", "services.sh" ]