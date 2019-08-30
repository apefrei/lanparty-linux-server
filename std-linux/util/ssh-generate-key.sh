#!/bin/bash

if test -z "$1"
then
    ssh-keygen -q -t rsa -b 4096 -f ~/.ssh/id_rsa -N ''
    exit 0
fi

UNAME="`getent passwd $1`"
if test -z "$UNAME"
then
    echo "ERROR: Unknown user $1 specified" >>/dev/stderr
    exit 1
fi

UHOME="`getent passwd $1 | cut -f6 -d:`"
if ! test -d "$UHOME"
then
    echo "ERROR: No home for user $1 found" >>/dev/stderr
    exit 1
fi

sudo su -c "ssh-keygen -q -t rsa -b 4096 -f ~/.ssh/id_rsa -N ''" -s /bin/sh $1
touch ~/.ssh/authorized_keys

# eof
