echo "### Setting up TELEGRAF for docker"

cp -R $DKR_PATH/configs-linux/etc-telegraf/telegraf.d/std-docker.conf /etc/telegraf/telegraf.d/std-docker.conf

if [ "$ENABLE_TELEGRAF" == "yes" ]
then
    systemctl restart telegraf
fi

#eof
