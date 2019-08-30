echo "### Setting up shorewall"
yum install shorewall fail2ban-shorewall fail2ban -y >> $LOGFILE 2>&1

mv /etc/fail2ban/jail.d/00-firewalld.conf /etc/fail2ban/jail.d/00-firewalld.conf.ORIG
cp $STD_PATH/configs-centos/etc-fail2ban/* /etc/fail2ban/jail.d/
sed -r -i "s/(.*)OUR_IPS_HERE(.*)$/\1$OUR_IPS_SPACED\2/g" /etc/fail2ban/jail.d/01-jail.conf

###

cp $STD_PATH/configs-centos/etc-shorewall/* /etc/shorewall/
sed -i 's/STARTUP_ENABLED=No/STARTUP_ENABLED=yes/' /etc/shorewall/shorewall.conf >> $LOGFILE
sed -i '$ a net         eth0            routefilter,tcpflags,logmartians' /etc/shorewall/interfaces >> $LOGFILE

IP=`hostname -I`
sed -i "s/PRIMARYIP=/PRIMARYIP=$IP/" /etc/shorewall/params >> $LOGFILE
sed -i "s/OURIPS=/OURIPS=$OUR_IPS/" /etc/shorewall/params >> $LOGFILE

echo -e "\
shorewall.conf\n\
blrules\n\
conntrack\n\
hosts\n\
interfaces\n\
lib.private\n\
Makefile\n\
params\n\
policy\n\
rules\n\
scfilter\n\
zones\
" > /tmp/shorewall-excludes

rsync --exclude-from '/tmp/shorewall-excludes' -a --remove-source-files /etc/shorewall/ /etc/shorewall/OTHERMODULES >> $LOGFILE
rm /tmp/shorewall-excludes

systemctl disable firewalld.service >> $LOGFILE 2>&1

if test "$ENABLE_FIREWALL" = "yes"
then
    systemctl enable fail2ban.service >> $LOGFILE 2>&1
    systemctl restart fail2ban.service >> $LOGFILE 2>&1
    systemctl enable shorewall.service >> $LOGFILE 2>&1
    echo "30    1    * * *   root    /usr/sbin/shorewall restart" >> /etc/crontab
else
    echo "#30    1    * * *   root    /usr/sbin/shorewall restart" >> /etc/crontab
fi
