echo "### Tuning system"

cp $STD_PATH/configs-fedora/etc-sysctl.d/blan-defaults.conf /etc/sysctl.d/blan-defaults.conf
echo "$STD_PATH/util/network-tuning.sh" >> /etc/rc.local
echo "$STD_PATH/util/rebuild-initramfs-once.sh" >> /etc/rc.local

systemctl disable rpcbind.service >> $LOGFILE 2>&1
