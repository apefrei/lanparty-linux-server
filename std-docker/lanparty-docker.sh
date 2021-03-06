#!/bin/bash

OLDDIR="`pwd`"
cd /root/scripts/lanparty
git pull >> /dev/null 2>&1
source /root/scripts/lanparty/common.inc
checkHostname
checkLockFile
checkBootstrapped
touch $LOGFILE
cd $DKR_PATH

#Define DOCKER vars
PORTAINER_PW=
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
source $DKR_PATH/parts-fedora/standard-docker-basics.inc
source $DKR_PATH/parts-fedora/standard-docker-telegraf.inc

markAsDone
#eof
