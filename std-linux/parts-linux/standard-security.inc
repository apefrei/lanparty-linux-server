echo "### Setting up security"

dnf -y install haveged ca-certificates >> $LOGFILE 2>&1
pip3 install xkcdpass >> $LOGFILE 2>&1
systemctl enable haveged >> $LOGFILE 2>&1
systemctl start haveged >> $LOGFILE 2>&1

mv /etc/security/limits.conf /etc/security/limits.conf.ORIG
cp $STD_PATH/configs-linux/etc-security/limits.conf /etc/security/limits.conf

sed -i -r "s/^SELINUX=.*/SELINUX=disabled/g" /etc/selinux/config

systemctl disable firewalld.service >> $LOGFILE 2>&1

#echo "PermitRootLogin yes" >> /etc/ssh/sshd_config
