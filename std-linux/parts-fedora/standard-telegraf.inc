echo "### Setting up telegraf"

cat > /etc/yum.repos.d/influxdb.repo << EOF
[influxdb]
name = InfluxDB Repository - RHEL
baseurl = https://repos.influxdata.com/rhel/7/x86_64/stable/
enabled = 1
gpgcheck = 1
gpgkey = https://repos.influxdata.com/influxdb.key
EOF

dnf -y install telegraf >> $LOGFILE 2>&1

rm -rf /etc/telegraf
cp -R $STD_PATH/configs-fedora/etc-telegraf /etc/telegraf

sed -r -i "s/(.*)STD_HOSTNAME(.*)$/\1$HNFULL\2/g" /etc/telegraf/telegraf.conf
sed -r -i "s/(.*)INFLUX_IP(.*)$/\1$INFLUX_IP\2/g" /etc/telegraf/telegraf.conf
sed -r -i "s/(.*)INFLUX_ADMIN(.*)$/\1$INFLUX_ADMIN\2/g" /etc/telegraf/telegraf.conf
sed -r -i "s/(.*)INFLUX_PW(.*)$/\1$INFLUX_PW\2/g" /etc/telegraf/telegraf.conf

if [ "$ENABLE_TELEGRAF" == "yes" ]
then
    systemctl enable telegraf
    systemctl start telegraf
fi
#eof
