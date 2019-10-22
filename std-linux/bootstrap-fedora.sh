#!/bin/bash

echo "### Initializing package repositories"
dnf -y install epel-release >> $LOGFILE 2>&1
dnf -y clean all >> $LOGFILE 2>&1

echo "### Installing base packages"
dnf -y install deltarpm >> $LOGFILE 2>&1
dnf -y upgrade >> $LOGFILE 2>&1
dnf -y update ca-certificates >> $LOGFILE 2>&1
dnf -y install acpid apg bzip2 gzip unzip htop nano nmap nload net-tools rsync \
               tcpdump telnet traceroute tree unzip uuid pciutils nvme-cli \
               wget curl whois readline-devel openssl-devel bash-completion \
               sshfs sysstat dbus vim iperf iftop screen symlinks >> $LOGFILE 2>&1

echo "### Setting up environment"
cp $STD_PATH/configs-fedora/.bashrc /root/
cp $STD_PATH/configs-fedora/.screenrc /root/
cp $STD_PATH/configs-fedora/.vimrc /root/
touch /root/.bashrc_local
mkdir /root/{dist,build,temp}
chmod -R +x /root/scripts/lanparty

source $STD_PATH/parts-fedora/standard-python3.inc
source $STD_PATH/parts-fedora/standard-security.inc
source $STD_PATH/parts-fedora/standard-ssh.inc
source $STD_PATH/parts-fedora/standard-ntp.inc
source $STD_PATH/parts-fedora/standard-snmp.inc
source $STD_PATH/parts-fedora/standard-tuning.inc
source $STD_PATH/parts-fedora/standard-telegraf.inc

echo "### Setting up services"
chmod +x /etc/rc.local
systemctl enable acpid.service >> $LOGFILE 2>&1
systemctl disable kdump.service >> $LOGFILE 2>&1
systemctl disable nfs-client.target >> $LOGFILE 2>&1
systemctl disable nfs-config.service >> $LOGFILE 2>&1
systemctl disable gssproxy.service >> $LOGFILE 2>&1

dnf -y remove polkit polkit-pkla-compat >> $LOGFILE 2>&1
chmod o=+r /usr/lib/systemd/system/auditd.service
chmod -x /usr/lib/systemd/system/ebtables.service
chmod -x /usr/lib/systemd/system/wpa_supplicant.service

###
echo "### Finishing installation"
echo "alias logtail=\"cd /var/log ; tail -f cron messages secure \"" >> /root/.bashrc_local
echo ""
echo ""
#eof
