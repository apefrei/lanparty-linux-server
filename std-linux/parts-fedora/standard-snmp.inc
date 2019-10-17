echo "### Setting up snmp"
dnf -y install net-snmp >> $LOGFILE 2>&1

mv /etc/snmp/snmpd.conf /etc/snmp/snmpd.conf.ORIG
cp $STD_PATH/configs-fedora/etc-snmp/snmpd.conf /etc/snmp/snmpd.conf

systemctl enable snmpd.service >> $LOGFILE 2>&1
