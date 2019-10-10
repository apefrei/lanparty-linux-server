#!/bin/bash

OLDDIR="`pwd`"
cd /root/scripts/blan
git pull >> /dev/null 2>&1
source /root/scripts/blan/common.inc
checkHostname
checkLockFile
checkBootstrapped
touch $LOGFILE
cd $GSM_PATH
chmod +x $GSM_PATH/scripts/*

#configure gameserver
GAMESERVER=""

echo "###"
echo "###"
echo "###"
echo "###"
echo
echo "### Standard setup for LinuxGSM"
echo "    Logfile: $LOGFILE"

# ATTENTION: Dependencies!!!
source $GSM_PATH/parts-fedora/standard-linuxgsm-components.inc
source $GSM_PATH/parts-fedora/standard-gameserver-environment

###
echo "### Finishing installation"

markAsDone

#eof
