echo "### Setting up system defaults"

yum -y install yum-cron >> $LOGFILE 2>&1
systemctl enable yum-cron >> $LOGFILE 2>&1
sed -i -r "s/(^emit_via = )stdio/\1email/g" /etc/yum/yum-cron.conf
sed -i -r "s/(^email_from = ).*$/\1$ADMIN_EMAIL/g" /etc/yum/yum-cron.conf

sed -i -r "s/(^GRUB_TIMEOUT=).*/\13/g" /etc/default/grub
$STD_PATH/util/update-grub.sh >> $LOGFILE 2>&1

sed -i -r "s/(^CREATE_MAIL_SPOOL=).*/\1no/g" /etc/default/useradd

