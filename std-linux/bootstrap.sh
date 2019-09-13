#!/bin/bash

source /root/scripts/blan/common.inc
checkHostname
checkLockFile
touch $LOGFILE
OLDDIR="`pwd`"
cd $STD_PATH

echo "###"
echo "###"
echo "###"
echo "###"
echo
echo "### Bootstrapping this system with Butterlan standards"
echo "    Logfile: $LOGFILE"
#askConfirmation

source $STD_PATH/bootstrap-fedora.sh

markAsDone
cd $OLDDIR

#eof
