echo "### Setting up nginx"

NGINX_OSRELEASE="7"
NGINX_BASEARCH="x86_64"

cat > /etc/yum.repos.d/nginx.repo << EOF
[nginx]
name=nginx repo
baseurl=http://nginx.org/packages/centos/$NGINX_OSRELEASE/$NGINX_BASEARCH/
gpgcheck=0
enabled=1
EOF

# Need to build from source, since no loadable module support yet 
yum -y install nginx >> $LOGFILE 2>&1

mv /etc/nginx /etc/nginx.ORIG
cp -R $PRX_PATH/configs-centos/etc-nginx /etc/nginx
mkdir -p /etc/nginx/sites-enabled

echo "### Our IP List"                    >> /etc/nginx/conf.d/global-maps.conf
echo "map \$remote_addr \$not-our-ips {"  >> /etc/nginx/conf.d/global-maps.conf
echo "default 1;"                         >> /etc/nginx/conf.d/global-maps.conf
for oip in $OUR_IPS_SPACED
do
    echo "$oip 0;" >> /etc/nginx/conf.d/global-maps.conf
done
echo "}" >> /etc/nginx/conf.d/global-maps.conf
echo >> /etc/nginx/conf.d/global-maps.conf

# generate a stronger DHE parameter 
# Using -dsaparam to speedup. See this for more information:
# https://security.stackexchange.com/questions/95178/diffie-hellman-parameters-still-calculating-after-24-hours
openssl dhparam -dsaparam -out /etc/nginx/dhparam.pem 4096 >> $LOGFILE 2>&1

systemctl enable nginx.service >> $LOGFILE 2>&1
systemctl start nginx.service >> $LOGFILE 2>&1
