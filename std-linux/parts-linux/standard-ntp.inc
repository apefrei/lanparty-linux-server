echo "### Setting up ntp"

dnf -y install chrony >> $LOGFILE 2>&1
systemctl enable chronyd.service >> $LOGFILE 2>&1
