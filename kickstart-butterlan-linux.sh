#!/bin/bash

test `whoami` == root || { echo "You need to be root!"; sudo su; }
test `whoami` == root || { echo "Upgrade to root did not work"; exit 1; }

echo "### Installing GIT"
yum -y install git > /dev/null 2>&1

echo "### Checking out from GIT"
test -d "/root/scripts" || mkdir -p $USERHOME/scripts
if ! test -d /root/scripts/blan/.git
then
    git clone --depth 1 https://bitbucket.org/apetomate/blan-host-bootstrap.git /root/scripts/blan
fi

if test -f "/root/scripts/blan/std-linux/bootstrap.sh"
then
    /root/scripts/blan/std-linux/bootstrap.sh
else
    echo "Cannot find bootstrap file. Aborting."
    exit 1
fi

# eof
