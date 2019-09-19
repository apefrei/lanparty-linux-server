cp -R $PRX_PATH/configs-fedora/etc-telegraf/conf.d/std-proxy-cache.conf /etc/telegraf/telegraf.d/std-proxy-cache.conf

systemctl restart telegraf
#eof
