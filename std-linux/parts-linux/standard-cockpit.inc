echo "### Setting up cockpit"
if [ "$ENABLE_COCKPIT" == "yes" ]
then
    dnf -y install cockpit >> $LOGFILE 2>&1
    systemctl enable --now cockpit.socket >> $LOGFILE 2>&1
else
    systemctl disable cockpit.service >> $LOGFILE 2>&1
    systemctl disable cockpit.socket >> $LOGFILE 2>&1
fi
#eof