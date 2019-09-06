echo "### Setting up security"

dnf -y install haveged ca-certificates >> $LOGFILE 2>&1
systemctl enable haveged >> $LOGFILE 2>&1
systemctl start haveged >> $LOGFILE 2>&1

mv /etc/security/limits.conf /etc/security/limits.conf.ORIG
cp $STD_PATH/configs-centos/etc-security/limits.conf /etc/security/limits.conf

#sed -i -r "s/^SELINUX=.*/SELINUX=disabled/g" /etc/selinux/config
sed -i -r "s/^SELINUX=.*/SELINUX=permissive/g" /etc/selinux/config
sed -i -r "s/(^Defaults.*requiretty)/\#\1/g" /etc/sudoers

git clone --depth 1 https://bitbucket.org/raptus-it-services/ssl-management-scripts.git /root/scripts/ssl-mgmt > /dev/null 2>&1

SSL_CERT_HOSTNAME="$HNFULL"
/root/scripts/ssl-mgmt/ssl-create-private-key-and-csr.sh "$SSL_CERT_HOSTNAME" "None of your business" "CH" "Nowhere" "$ADMIN_EMAIL" >> $LOGFILE 2>&1
/root/scripts/ssl-mgmt/ssl-create-selfsigned-sslcert.sh /etc/ssl/waiting/$SSL_CERT_HOSTNAME.csr /etc/ssl/waiting/$SSL_CERT_HOSTNAME.key >> $LOGFILE 2>&1
/root/scripts/ssl-mgmt/ssl-create-pem.sh /etc/ssl/waiting/$SSL_CERT_HOSTNAME.key /etc/ssl/waiting/$SSL_CERT_HOSTNAME.crt >> $LOGFILE 2>&1

mkdir /etc/ssl/selfsigned_$SSL_CERT_HOSTNAME
mv /etc/ssl/waiting/$SSL_CERT_HOSTNAME.* /etc/ssl/selfsigned_$SSL_CERT_HOSTNAME/
