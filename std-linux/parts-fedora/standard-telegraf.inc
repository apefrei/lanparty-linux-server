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

rm /etc/telegraf
cp -R $PRX_PATH/configs-fedora/etc-telegraf /etc/telegraf

sed -r -i "s/(.*)STD_HOSTNAME(.*)$/\1$HNFULL\2/g" /etc/telegraf.conf

systemctl enable telegraf
systemctl start telegraf
#eof
