#!/bin/bash

echo "### Initializing package repositories"
dnf -y clean all >> $LOGFILE 2>&1

echo "### Installing base packages"
dnf -y upgrade >> $LOGFILE 2>&1
dnf -y install epel-release >> $LOGFILE 2>&1
rpm --import https://www.elrepo.org/RPM-GPG-KEY-elrepo.org >> $LOGFILE 2>&1
dnf -y install https://www.elrepo.org/elrepo-release-8.el8.elrepo.noarch.rpm >> $LOGFILE 2>&1
dnf -y update ca-certificates >> $LOGFILE 2>&1
dnf -y install acpid bzip2 gzip unzip nano nmap net-tools rsync dmidecode \
               tcpdump telnet traceroute tree unzip uuid pciutils nvme-cli \
               wget curl readline-devel openssl-devel bash-completion polkit \
               sysstat dbus vim iperf3 iftop screen symlinks tar dnf-utils >> $LOGFILE 2>&1

echo "### Setting up environment"
rm -f /root/.bashrc && cp $STD_PATH/configs-linux/.bashrc /root/
cp $STD_PATH/configs-linux/.screenrc /root/
cp $STD_PATH/configs-linux/.vimrc /root/
touch /root/.bashrc_local
mkdir /root/{dist,build,temp}
chmod -R +x /root/scripts/lanparty

source $STD_PATH/parts-linux/standard-kernel.inc
source $STD_PATH/parts-linux/standard-python3.inc
source $STD_PATH/parts-linux/standard-security.inc
source $STD_PATH/parts-linux/standard-ssh.inc
source $STD_PATH/parts-linux/standard-ntp.inc
source $STD_PATH/parts-linux/standard-snmp.inc
source $STD_PATH/parts-linux/standard-tuning.inc
source $STD_PATH/parts-linux/standard-telegraf.inc
source $STD_PATH/parts-linux/standard-cockpit.inc

echo "### Setting up services"
chmod +x /etc/rc.local
systemctl enable acpid.service >> $LOGFILE 2>&1
systemctl disable kdump.service >> $LOGFILE 2>&1

dnf -y remove polkit polkit-pkla-compat >> $LOGFILE 2>&1
chmod o=+r /usr/lib/systemd/system/auditd.service

###
echo "### Finishing installation"
echo "alias logtail=\"cd /var/log ; tail -f cron messages secure \"" >> /root/.bashrc_local
echo ""
echo ""
#eof
