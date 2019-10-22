#!/bin/bash
#
# Need to rebuild initram FS due to changes of sysctl
#

LOCKFILE="/var/lanparty/lock/rebuild-initramfs.lock"

if ! test -f "$LOCKFILE"
then
    touch "$LOCKFILE"
    /root/scripts/lanparty/std-linux/util/rebuild-initramfs.sh > /dev/null 2>&1 &
fi

# eof
