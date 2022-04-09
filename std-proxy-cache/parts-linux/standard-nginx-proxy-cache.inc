echo "### Setting up NGINX Proxy Cache"

{
        echo '[nginx-stable]'
        echo 'name=nginx stable repo'
        echo 'baseurl=http://nginx.org/packages/centos/$releasever/$basearch/'
        echo 'gpgcheck=1'
        echo 'enabled=1'
        echo 'gpgkey=https://nginx.org/keys/nginx_signing.key'  
        echo 'module_hotfixes=true'
} >> /etc/yum.repos.d/nginx.repo

# Install nginx
yum-config-manager --enable nginx-stable >> $LOGFILE 2>&1
dnf -y install nginx >> $LOGFILE 2>&1

cd $PRX_PATH

# Copy configuration
rm -rf /etc/nginx
cp -R $PRX_PATH/configs-linux/etc-nginx /etc/nginx
mkdir -p /etc/nginx/sites-enabled

ln -sf /etc/nginx/sites-available/* /etc/nginx/sites-enabled/

# Configure variables
set -e
echo "worker_processes ${NGINX_WORKER_PROCESSES};" > /etc/nginx/workers.conf
sed -i "s/CACHE_INDEX_SIZE/${CACHE_INDEX_SIZE}/" /etc/nginx/conf.d/20_proxy_cache_path.conf
sed -i "s/CACHE_DISK_SIZE/${CACHE_DISK_SIZE}/" /etc/nginx/conf.d/20_proxy_cache_path.conf
sed -i "s/CACHE_MAX_AGE/${CACHE_MAX_AGE}/" /etc/nginx/sites-available/generic.conf.d/root/20_cache.conf
sed -i "s/CACHE_MAX_AGE/${CACHE_MAX_AGE}/" /etc/nginx/conf.d/20_proxy_cache_path.conf
sed -i "s/UPSTREAM_DNS/${UPSTREAM_DNS}/" /etc/nginx/sites-available/generic.conf.d/10_generic.conf
sed -i "s/UPSTREAM_DNS/${UPSTREAM_DNS}/" /etc/nginx/streams-available/10_generic.conf

$PRX_PATH/scripts/update-domain-maps.sh >> $LOGFILE 2>&1

chown -R nginx:nginx /data/

systemctl enable nginx.service >> $LOGFILE 2>&1
systemctl start nginx.service >> $LOGFILE 2>&1
#eof
