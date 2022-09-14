#!/bin/bash

OLDDIR="`pwd`"
cd /root/scripts/lanparty
git pull --rebase >> /dev/null 2>&1
source /root/scripts/lanparty/common.inc
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

echo "### Standard setup for docker environment"
echo "    Logfile: $LOGFILE"

# ATTENTION: Dependencies!!!
source $DKR_PATH/parts-linux/standard-docker-basics.inc
source $DKR_PATH/parts-linux/standard-docker-telegraf.inc

markAsDone
#eof
