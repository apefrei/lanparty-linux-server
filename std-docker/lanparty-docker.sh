#!/bin/bash

OLDDIR="`pwd`"

# re-clone whole git repo
cd ~
rm -rf /root/scripts/lanparty
git clone --depth 1 https://github.com/apefrei/lanparty-linux-server.git /root/scripts/lanparty >> /dev/null 2>&1
cd /root/scripts/lanparty

# prechecks
source /root/scripts/lanparty/common.inc
checkHostname
checkLockFile
checkBootstrapped
touch $LOGFILE
cd $DKR_PATH

# install params
USE_REVERSE_PROXY=
LETSENCRYPT_EMAIL=
PORTAINER_VHOSTNAME=
DKRCFG="/root/.dkrcfg"
if ! test -f "/root/.dkrcfg"
then
    echo "### Cannot find the configuration file: $DKRCFG"
    echo "EXITING"
    exit 1
else
    source "$DKRCFG"
fi

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
