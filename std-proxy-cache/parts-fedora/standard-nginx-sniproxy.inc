echo "### Setting up NGINX SNI-Proxy"

mkdir -p /etc/nginx/streams-enabled
ln -sf /etc/nginx/streams-available/* /etc/nginx/streams-enabled/

systemctl restart nginx.service >> $LOGFILE 2>&1
#eof
