#!/bin/bash

OLDDIR="`pwd`"
cd /root/scripts/blan
git pull >> /dev/null
source /root/scripts/blan/common.inc
checkHostname
checkInstall
checkLockFile
checkBootstrapped
touch $LOGFILE
cd $DKR_PATH

echo "###"
echo "###"
echo "###"
echo "###"
echo "###"
echo "###"
echo "###"
echo

echo "### Standard setup for Docker Environment"
echo "    Logfile: $LOGFILE"
askConfirmation

echo "### Setting up basic structure"
mkdir -p /home/archived
mkdir -p /home/docker/volumes

# ATTENTION: Dependencies!!!
source $DKR_PATH/parts-centos/standard-webserver.inc
source $DKR_PATH/parts-centos/standard-memcached.inc
source $DKR_PATH/parts-centos/standard-nginx.inc

chown -R nginx:nginx /home/restricted/logs
chown -R nginx:nginx /home/restricted/temp

echo "### Finishing installation"
echo "alias logtail=\"cd /var/log ; tail -f cron dmesg maillog messages secure nginx/error.log /home/sites/*/pub/log/*.log\"" >> /root/.bashrc_local

markAsDone
cd $OLDDIR

# eof
