echo "### Setting up ntp"
yum -y install ntp >> $LOGFILE 2>&1
sed -i -r "s/^(server)/#\1/g" /etc/ntp.conf
echo -e "\nserver ch.pool.ntp.org" >> /etc/ntp.conf
echo -e "\ninterface ignore wildcard" >> /etc/ntp.conf
echo -e "\ninterface listen 127.0.0.1" >> /etc/ntp.conf

systemctl enable ntpd.service >> $LOGFILE 2>&1
