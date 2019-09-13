echo "### Installing base packages"

dnf -y install sniproxy >> $LOGFILE 2>&1

rm /etc/sniproxy.conf
cp -R $PRX_PATH/configs-fedora/etc-sniproxy/sniproxy.conf /etc/sniproxy.conf
