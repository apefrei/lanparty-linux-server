echo "### Setting up TELEGRAF for nginx"

cp -R $PRX_PATH/configs-fedora/etc-telegraf/telegraf.d/std-proxy-cache.conf /etc/telegraf/telegraf.d/std-proxy-cache.conf
systemctl restart telegraf >> $LOGFILE 2>&1
#eof
