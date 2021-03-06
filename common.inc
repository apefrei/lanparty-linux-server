
# Defaults & Helpers
#

STD_PATH=/root/scripts/lanparty/std-linux
PRX_PATH=/root/scripts/lanparty/std-proxy-cache
DKR_PATH=/root/scripts/lanparty/std-docker
GSM_PATH=/root/scripts/lanparty/std-linuxgsm

# Colors
red="\033[0;31m"
green="\033[0;32m"
nc="\033[0m"

HNFULL="`hostnamectl status | sed -r -n 's/^.*Static hostname: (.*)$/\1/p'`"

# Define TELEGRAF vars
ENABLE_TELEGRAF=
INFLUX_IP=
INFLUX_ADMIN=
INFLUX_PW=
STDCFG="/root/.stdcfg"
if test -f "$STDCFG"
then
    source "$STDCFG"
fi

if test "$0" = "-bash"
then
    SCRIPTID="`uuid`"
else
    SCRIPTID="`basename $0 | head -c -4`"
fi

TEMPDIR="/var/lanparty/tmp"
LOCKDIR="/var/lanparty/lock"
LOGDIR="/var/lanparty/log"
STATEDIR="/var/lanparty/state"
LOCKFILE="$LOCKDIR/$SCRIPTID.done"
LOCKFILE_BSTRAP="$LOCKDIR/bootstrap.done"
LOGFILE="$LOGDIR/$SCRIPTID-`date +%Y%m%d-%H%M`.log"
APGOPTS="-n1 -m15 -x15 -a0 -q -M CL"
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

function markAsDoneGSM
{
    echo "`date`" > "$LOCKFILE_BSTRAP"
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

#
# Call this function with: <purpose> <username> <password> [address]
#
function passwordInfo
{
    PWDFILE="/root/generated-passwords.txt"
    if ! test -f "$PWDFILE"
    then
        echo "Generated passwords for $SCRIPTID" >> $PWDFILE
        echo "" >> $PWDFILE
        chmod u=+rw,go= $PWDFILE
    fi

    echo "$1  Username: $2  Password: $3     Address: $4" >> $PWDFILE
    echo
    echo "    ATTENTION"
    echo -e "    A Password has been generated for ${green}$1${nc}, please see in $PWDFILE"
    echo
}

# eof
