echo "### Setting up TELEGRAF for nginx"

cp -R $PRX_PATH/configs-linux/etc-telegraf/telegraf.d/std-proxy-cache.conf /etc/telegraf/telegraf.d/std-proxy-cache.conf

if [ "$ENABLE_TELEGRAF" == "yes" ]
then
    systemctl restart telegraf
fi

#eof
