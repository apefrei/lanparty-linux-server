echo "### Installing base packages"

yum -y install lynx mailx certbot-nginx >> $LOGFILE 2>&1
