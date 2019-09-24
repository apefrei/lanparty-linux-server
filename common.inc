#
# Defaults & Helpers
#

STD_PATH=/root/scripts/blan/std-linux
PRX_PATH=/root/scripts/blan/std-proxy-cache

HNFULL="`hostnamectl status | sed -r -n 's/^.*Static hostname: (.*)$/\1/p'`"

ENABLE_TELEGRAF=
INFLUX_IP=
INFLUX_ADMIN=
INFLUX_PW=
CFGFILE="/root/.lxcfg"
if test -f "$CFGFILE"
then
    source "$CFGFILE"
fi

if test "$0" = "-bash"
then
    SCRIPTID="`uuid`"
else
    SCRIPTID="`basename $0 | head -c -4`"
fi

TEMPDIR="/var/blan/tmp"
LOCKDIR="/var/blan/lock"
LOGDIR="/var/blan/log"
STATEDIR="/var/blan/state"
LOCKFILE="$LOCKDIR/$SCRIPTID.done"
LOCKFILE_BSTRAP="$LOCKDIR/bootstrap.done"
LOGFILE="$LOGDIR/$SCRIPTID-`date +%Y%m%d-%H%M`.log"
MACHINE_TYPE="physical"
MACHINE_INFO="n/a"

test -d "$TEMPDIR" || { mkdir -p "$TEMPDIR"; }
test -d "$LOCKDIR" || { mkdir -p "$LOCKDIR"; }
test -d "$LOGDIR" || { mkdir -p "$LOGDIR"; }
test -d "$STATEDIR" || { mkdir -p "$STATEDIR"; }

function checkHostname
{
    if ! test "`echo ${HNFULL} | grep -oc '\.'`" = "1"
    then
        echo "The hostname $HNFULL is not set correctly, please use a FQDN."
        exit 1
    fi
}

function checkLockFile
{
    test -d "$LOCKDIR" || { mkdir -p "$LOCKDIR"; chmod go= "$LOCKDIR"; }
    if test -f "$LOCKFILE"
    then
        echo "This script should only be executed once."
        echo "If you want to override that, please follow this procedure:"
        echo
        echo "1. Know what you are doing!"
        echo "2. Remove the lock file $LOCKFILE"
        exit 1
    fi

    touch "$LOCKFILE"
}

function checkBootstrapped
{
    if ! test -f "$LOCKFILE_BSTRAP"
    then
        echo "Oops, you need to bootstrap first!"
        exit 1
    fi
}

function markAsDone
{
    echo "### Done"
    echo
    echo "Please reboot now, before doing anything with this system"
    echo

    echo "`date`" > "$LOCKFILE_BSTRAP"
}

#
# Call this function with: <URL> <DestinationPath>
#
function getFileFromURL
{
    URL=$1
    DSTPATH=$2
    DSTFILE="`echo "${URL##*/}"`"
    if test -z "$URL" ||
       test -z "$DSTPATH" ||
       test -z "$DSTFILE"
    then
        echo "Cannot get file from URL ($URL)" >> /dev/stderr
        return
    fi

    curl --silent -o "$DSTPATH/$DSTFILE" "$URL"
    if ! test -f "$DSTPATH/$DSTFILE"
    then
        echo "Failed to download file to $DSTPATH/$DSTFILE" >> /dev/stderr
    fi
}

# eof
