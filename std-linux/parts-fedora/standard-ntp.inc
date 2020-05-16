echo "### Setting up ntp"
dnf -y install chrony >> $LOGFILE 2>&1
sed -i -r "s/^(pool)/#\1/g" /etc/chrony.conf
echo -e "\npool ch.pool.ntp.org iburst" >> /etc/chrony.conf

systemctl enable chronyd.service >> $LOGFILE 2>&1
