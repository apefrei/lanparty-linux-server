#!/bin/bash

OLDDIR="`pwd`"
cd /root/scripts/blan
git pull >> /dev/null 2>&1
source /root/scripts/blan/common.inc
checkHostname
checkLockFile
checkBootstrapped
touch $LOGFILE
cd $DKR_PATH



echo "###"
echo "###"
echo "###"
echo "###"
echo

echo "### Standard setup for proy cache"
echo "    Logfile: $LOGFILE"

# ATTENTION: Dependencies!!!
source $DKR_PATH/parts-fedora/standard-docker-basics.inc
source $DKR_PATH/parts-fedora/standard-docker-telegraf.inc
#eof
