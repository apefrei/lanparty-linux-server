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
GAMESERVER=

echo "###"
echo "###"
echo "###"
echo "###"
echo

echo "### Standard setup for linuxgsm cache"
echo "    Logfile: $LOGFILE"

echo "### Chose your Gameserver"
TEMP_PATH=$(mktemp -d)
cd $TEMP_PATH
wget -O linuxgsm.sh https://linuxgsm.sh >> $LOGFILE 2>&1
chmod +x linuxgsm.sh
./linuxgsm.sh list



if [ -d "/data/storage1" ]
then
    mkdir -m 755 -p /data/storage1/cache
else
    echo "Cannot find cache folder /data/storage1. This setup is made for two identical disk storages"
    exit 1
fi
if [ -d "/data/storage1" ]
then
    mkdir -m 755 -p /data/storage2/cache
else
    echo "Cannot find cache folder /data/storage2. This setup is made for two identical disk storages"
    exit 1
fi

# ATTENTION: Dependencies!!!
source $GSM_PATH/parts-fedora/standard-linuxgsm-components.inc
source $GSM_PATH/parts-fedora/standard-gameserver.inc

###
echo "### Finishing installation"
#echo "alias logtail=\"cd /var/log ; tail -f cron messages secure /data/*/logs/*.log\"" >> /root/.bashrc_local
#echo ""
#echo ""

markAsDone

#eof
