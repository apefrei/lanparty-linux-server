echo "### Setting up postfix"

# Needed for smtp auth
yum -y install cyrus-sasl-plain  >> $LOGFILE 2>&1

mv /etc/postfix/main.cf /etc/postfix/main.cf.ORIG
cp $STD_PATH/configs-centos/etc-postfix/main.cf /etc/postfix/main.cf

mv /etc/aliases /etc/aliases.ORIG
cat > /etc/aliases << EOF
# See man 5 aliases for format
postmaster:    root
root:          $ADMIN_EMAIL
EOF

newaliases
cd /etc/postfix
ln -s ../aliases

