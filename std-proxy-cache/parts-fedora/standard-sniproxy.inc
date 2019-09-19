echo "### Setting up SNIPROXY"

# Install dependencies
dnf -y install golang >> $LOGFILE 2>&1

# Install software
TEMP_PATH=$(mktemp -d)
cd $TEMP_PATH
wget $FABLNK >> $LOGFILE 2>&1
wget $FABCNF >> $LOGFILE 2>&1
mkdir /opt/fabio
cp fabio.properties /opt/fabio/fabio.conf
cp fabio-* /opt/fabio/fabio
chmod +x /opt/fabio/fabio
rm -rf $TEMP_PATH

useradd -M -d /opt/fabio -s /sbin/nologin fabio
setcap 'cap_net_bind_service=+ep' /opt/fabio/fabio

# Create Service
cat > /etc/systemd/system/fabio.service << EOF
[Unit]
Description=Fabio SNI-Proxy
After=syslog.target
After=network.target

[Service]
LimitMEMLOCK=infinity
LimitNOFILE=65535

Type=simple
WorkingDirectory=/opt/fabio
Restart=always
ExecStart=/opt/fabio/fabio -cfg /opt/fabio/fabio.conf

StandardOutput=syslog
StandardError=syslog
SyslogIdentifier=fabio

PrivateDevices=yes
PrivateTmp=yes
ProtectSystem=full
ProtectHome=yes

AmbientCapabilities=CAP_NET_BIND_SERVICE
RestrictAddressFamilies=AF_INET AF_INET6 AF_UNIX AF_NETLINK

User=fabio
Group=fabio

[Install]
WantedBy=multi-user.target
EOF

chmod 744 /etc/systemd/system/fabio.service
chown -R fabio:fabio /opt/fabio

systemctl enable fabio.service
systemctl daemon-reload
systemctl start fabio.service
