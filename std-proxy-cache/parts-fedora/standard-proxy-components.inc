echo "### Installing base packages"

dnf -y install jq inotify-tools >> $LOGFILE 2>&1
