echo "### Setting up system defaults"

yum -y install yum-cron >> $LOGFILE 2>&1
systemctl enable yum-cron >> $LOGFILE 2>&1

sed -i -r "s/(^GRUB_TIMEOUT=).*/\13/g" /etc/default/grub
$STD_PATH/util/update-grub.sh >> $LOGFILE 2>&1
