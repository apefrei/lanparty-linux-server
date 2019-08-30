echo "### Setting up snmp"
yum -y install net-snmp >> $LOGFILE 2>&1

mv /etc/snmp/snmpd.conf /etc/snmp/snmpd.conf.ORIG
cp $STD_PATH/configs-centos/etc-snmp/snmpd.conf /etc/snmp/snmpd.conf
sed -r -i "s/(HOSTMASTER).*$/\1$ADMIN_EMAIL/g" /etc/snmp/snmpd.conf

systemctl enable snmpd.service >> $LOGFILE 2>&1
