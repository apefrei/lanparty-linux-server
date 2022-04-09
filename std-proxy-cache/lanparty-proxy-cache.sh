#!/bin/bash

OLDDIR="`pwd`"
cd /root/scripts/lanparty
git pull >> /dev/null 2>&1
source /root/scripts/lanparty/common.inc
checkHostname
checkLockFile
checkBootstrapped
touch $LOGFILE
cd $PRX_PATH
chmod +x $PRX_PATH/scripts/*

#Define NGINX Proxy vars
CACHE_INDEX_SIZE=
CACHE_DISK_SIZE=
CACHE_MAX_AGE=
UPSTREAM_DNS=
LOGFILE_RETENTION=
PRXCFG="/root/.prxcfg"
if ! test -f "/root/.prxcfg"
then
    echo "### Cannot find the configuration file: $PRXCFG"
    echo "EXITING"
    exit 1
else
    source "$PRXCFG"
fi

echo "###"
echo "###"
echo "###"
echo "###"
echo

echo "### Standard setup for nginx proxy cache"
echo "    Logfile: $LOGFILE"

echo "### Setting up basic structure"

mkdir -m 755 -p /data/local/logs
mkdir -m 755 -p /data/local/info
mkdir -m 755 -p /data/local/cachedomains
mkdir -m 755 -p /tmp/nginx/

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
source $PRX_PATH/parts-linux/standard-proxy-components.inc
source $PRX_PATH/parts-linux/standard-nginx-proxy-cache.inc
source $PRX_PATH/parts-linux/standard-nginx-sniproxy.inc
source $PRX_PATH/parts-linux/standard-nginx-telegraf.inc

###
echo "### Finishing installation"
echo "alias logtail=\"cd /var/log ; tail -f cron messages secure /data/*/logs/*.log\"" >> /root/.bashrc_local
echo ""
echo ""

markAsDone

#eof
