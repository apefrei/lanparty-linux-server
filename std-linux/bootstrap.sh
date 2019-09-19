#!/bin/bash

source /root/scripts/blan/common.inc
checkHostname
checkLockFile
touch $LOGFILE
OLDDIR="`pwd`"
cd $STD_PATH

echo "###"
echo
echo '______ _   _ _____ _____ ___________ _       ___   _   _        _     _____ _   _ _   ___   __'
echo '| ___ \ | | |_   _|_   _|  ___| ___ \ |     / _ \ | \ | |      | |   |_   _| \ | | | | \ \ / /'
echo '| |_/ / | | | | |   | | | |__ | |_/ / |    / /_\ \|  \| |______| |     | | |  \| | | | |\ V / '
echo '| ___ \ | | | | |   | | |  __||    /| |    |  _  || . ` |______| |     | | | . ` | | | |/   \ '
echo '| |_/ / |_| | | |   | | | |___| |\ \| |____| | | || |\  |      | |_____| |_| |\  | |_| / /^\ \'
echo '\____/ \___/  \_/   \_/ \____/\_| \_\_____/\_| |_/\_| \_/      \_____/\___/\_| \_/\___/\/   \/'
echo
echo
echo "### Bootstrapping this system with BUTTERLAN standards"
echo "    Logfile: $LOGFILE"

source $STD_PATH/bootstrap-fedora.sh

markAsDone
cd $OLDDIR

#eof
