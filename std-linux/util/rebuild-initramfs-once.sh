#!/bin/bash
#
# Need to rebuild initram FS due to changes of sysctl
#

LOCKFILE="/var/blan/lock/rebuild-initramfs.lock"

if ! test -f "$LOCKFILE"
then
    touch "$LOCKFILE"
    /root/scripts/blan/std-linux/util/rebuild-initramfs.sh > /dev/null 2>&1 &
fi

# eof
