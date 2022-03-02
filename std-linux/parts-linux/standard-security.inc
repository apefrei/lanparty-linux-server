echo "### Setting up security"

dnf -y install haveged ca-certificates >> $LOGFILE 2>&1
pip3 install xkcdpass >> $LOGFILE 2>&1
systemctl enable haveged >> $LOGFILE 2>&1
systemctl start haveged >> $LOGFILE 2>&1

mv /etc/security/limits.conf /etc/security/limits.conf.ORIG
cp $STD_PATH/configs-linux/etc-security/limits.conf /etc/security/limits.conf

sed -i -r "s/^SELINUX=.*/SELINUX=disabled/g" /etc/selinux/config
#sed -i -r "s/^SELINUX=.*/SELINUX=permissive/g" /etc/selinux/config
sed -i -r "s/(^Defaults.*requiretty)/\#\1/g" /etc/sudoers

systemctl disable firewalld.service >> $LOGFILE 2>&1

echo "PermitRootLogin yes" >> /etc/ssh/sshd_config

git clone --depth 1 https://bitbucket.org/raptus-it/ssl-management-scripts.git /root/scripts/ssl-mgmt > /dev/null 2>&1
