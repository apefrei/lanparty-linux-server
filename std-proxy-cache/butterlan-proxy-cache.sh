#!/bin/bash

OLDDIR="`pwd`"
cd /root/scripts/blan
git pull >> /dev/null
source /root/scripts/blan/common.inc
checkHostname
checkLockFile
checkBootstrapped
touch $LOGFILE
cd $PRX_PATH
chmod +x $PRX_PATH/configs-fedora/scripts/*

#Define NGINX Proxy vars
GENERICCACHE_VERSION="2"
CACHE_MEM_SIZE="4000m"
CACHE_DISK_SIZE="3200000m"
CACHE_MAX_AGE="3560d"
UPSTREAM_DNS="192.168.88.1"
BEAT_TIME="1h"
LOGFILE_RETENTION="3560"
NGINX_WORKER_PROCESSES="auto"
CACHE_DOMAIN_REPO="https://github.com/uklans/cache-domains.git"

#Define FABIO sniproxy vars
FABLNK="https://github.com/fabiolb/fabio/releases/download/v1.5.11/fabio-1.5.11-go1.11.5-linux_amd64"
FABCNF="https://raw.githubusercontent.com/fabiolb/fabio/master/fabio.properties"

echo "###"
echo "###"
echo "###"
echo "###"
echo

echo "### Standard setup for proy cache"
echo "    Logfile: $LOGFILE"

echo "### Setting up basic structure"

mkdir -m 755 -p /data/local/logs
mkdir -m 755 -p /data/local/info
mkdir -m 755 -p /data/local/cachedomains
mkdir -m 755 -p /tmp/nginx/

if test "/data/storage1"
then
    mkdir -m 755 -p /data/storage1/cache
else
    echo "Cannot find cache folder /data/storage1. This setup is made for two identical disk storages"
    exit 1
fi
if test "/data/storage2"
then
    mkdir -m 755 -p /data/storage2/cache
else
    echo "Cannot find cache folder /data/storage2. This setup is made for two identical disk storages"
    exit 1
fi

# ATTENTION: Dependencies!!!
source $WEB_PATH/parts-centos/standard-proxy-components.inc
source $WEB_PATH/parts-centos/standard-nginx-proxy-cache.inc
source $WEB_PATH/parts-centos/standard-sniproxy.inc
source $WEB_PATH/parts-centos/standard-nginx-telegraf.inc

###

echo "### Finishing installation"
echo "alias logtail=\"cd /var/log ; tail -f cron dmesg messages secure nginx/error.log /data/*/logs/*.log\"" >> /root/.bashrc_local
