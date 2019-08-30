echo "### Setting up fstrim"

systemctl enable fstrim.timer >> $LOGFILE 2>&1
