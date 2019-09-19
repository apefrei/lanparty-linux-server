echo "### Setting up telegraf"

cat<<EOF | tee /etc/yum.repos.d/influxdb.repo
[influxdb]
name = InfluxDB Repository - RHEL
baseurl = https://repos.influxdata.com/rhel/7/x86_64/stable/
enabled = 1
gpgcheck = 1
gpgkey = https://repos.influxdata.com/influxdb.key
EOF

dnf -y install telegraf >> $LOGFILE 2>&1

mv /etc/telegraf.conf /etc/snmp/telegraf.conf.ORIG
cp $STD_PATH/configs-fedora/etc-telegraf/telegraf.conf /etc/telegraf.conf

sed -r -i "s/(.*)STD_HOSTNAME(.*)$/\1$HNFULL\2/g" /etc/telegraf.conf

sudo systemctl enable telegraf
sudo systemctl start telegraf
#eof
