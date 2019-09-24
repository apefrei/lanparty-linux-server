#!/bin/bash

if ! test -f "/root/.lxcfg"
then
    echo "### Cannot find the configuration file: $CFGFILE"
    echo ""
    echo "    Missing configuration:"
    echo ""
    echo "        ENABLE_TELEGRAF=yes                # Enable Telegraf Service"
    echo "        INFLUX_IP=<ipv4>                   # IP of INFLUXDB Service"
    echo "        INFLUX_ADMIN=<username>            # Username of INFLUXDB Admin"
    echo "        INFLUX_PW=<password>               # Password of INFLUXDB Admin"
    echo ""
    exit 1
fi

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
