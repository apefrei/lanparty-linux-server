echo "### Setting up basic components for LinxGSM"
dnf -y install mailx postfix file binutils bc jq tmux glibc.i686 libstdc++ libstdc++.i686 >> $LOGFILE 2>&1
