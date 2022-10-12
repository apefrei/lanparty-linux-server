echo "### Tuning system"

cp $STD_PATH/configs-linux/etc-sysctl.d/lanparty-defaults.conf /etc/sysctl.d/lanparty-defaults.conf
chmod +x $STD_PATH/scripts/network-tuning.sh
chmod +x $STD_PATH/scripts/rebuild-initramfs-once.sh
echo "$STD_PATH/scripts/network-tuning.sh" >> /etc/rc.local
echo "$STD_PATH/scripts/rebuild-initramfs-once.sh" >> /etc/rc.local
