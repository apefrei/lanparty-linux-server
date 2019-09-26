echo "### Setting up NGINX Proxy Cache - This can take a while (recompiling)"

# Install nginx
dnf -y install nginx >> $LOGFILE 2>&1

# Recompile NGINX with multi-threading
dnf -y install gcc gcc-c++ make glibc-devel libaio-devel \
               pcre-devel zlib-devel openssl-devel glibc \
               libxslt libxslt-devel libxml2 libxml2-devel libXpm-devel \
               glibc-headers libevent libpthread.so.0 gd-devel \
               libcrypt.so.1 libstdc++.so.6 librt.so.1 libm.so.6 \
               libssl.so.10 libcrypto.so.10 libdl.so.2 gperftools-devel \
               libz.so.1 libgcc_s.so.1 libc.so.6 /lib64/ld-linux-x86-64.so.2 \
               libfreebl3.so libgssapi_krb5.so.2 libkrb5.so.3 libcom_err.so.2 \
               libk5crypto.so.3 libkrb5support.so.0 libkeyutils.so.1 \
               libresolv.so.2 libselinux.so.1 >> $LOGFILE 2>&1

command="nginx -v"
nginxv=$( ${command} 2>&1 )
nginxlocal=$(echo $nginxv | grep -o '[0-9.]*')

TEMP_PATH=$(mktemp -d)
cd $TEMP_PATH
wget http://nginx.org/download/nginx-$nginxlocal.tar.gz >> $LOGFILE 2>&1
tar -xvzf nginx-$nginxlocal.tar.gz >> $LOGFILE 2>&1
cd $TEMP_PATH/nginx-$nginxlocal

./configure --prefix=/usr/share/nginx \
--sbin-path=/usr/sbin/nginx \
--modules-path=/usr/lib64/nginx/modules \
--conf-path=/etc/nginx/nginx.conf \
--error-log-path=/var/log/nginx/error.log \
--http-log-path=/var/log/nginx/access.log \
--http-client-body-temp-path=/var/lib/nginx/tmp/client_body \
--http-proxy-temp-path=/var/lib/nginx/tmp/proxy \
--http-uwsgi-temp-path=/var/lib/nginx/tmp/uwsgi \
--pid-path=/run/nginx.pid \
--lock-path=/run/lock/subsys/nginx \
--user=nginx --group=nginx --build=Fedora --with-file-aio --with-threads \
--with-http_ssl_module --with-http_v2_module --with-http_realip_module --with-stream_ssl_preread_module \
--with-http_addition_module --with-http_xslt_module --with-http_image_filter_module \
--with-http_sub_module --with-http_dav_module --with-http_flv_module --with-http_mp4_module \
--with-http_gunzip_module --with-http_gzip_static_module --with-http_random_index_module \
--with-http_secure_link_module --with-http_degradation_module --with-http_slice_module \
--with-http_stub_status_module --with-http_auth_request_module \
--with-mail=dynamic --with-mail_ssl_module --with-pcre --with-pcre-jit --with-stream \
--with-stream_ssl_module --with-stream_ssl_preread_module --with-google_perftools_module --with-debug \
--with-cc-opt='-O2 -g -pipe -Wall -Werror=format-security -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -fexceptions -fstack-protector-strong -grecord-gcc-switches -m64 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection' >> $LOGFILE 2>&1

make >> $LOGFILE 2>&1
make install >> $LOGFILE 2>&1
cd $PRX_PATH
rm -rf $TEMP_PATH

# Copy configuration
rm -rf /etc/nginx
cp -R $PRX_PATH/configs-fedora/etc-nginx /etc/nginx
mkdir -p /etc/nginx/sites-enabled

ln -sf /etc/nginx/sites-available/* /etc/nginx/sites-enabled/

# Configure variables
set -e
echo "worker_processes ${NGINX_WORKER_PROCESSES};" > /etc/nginx/workers.conf
sed -i "s/CACHE_MEM_SIZE/${CACHE_MEM_SIZE}/"  /etc/nginx/conf.d/20_proxy_cache_path.conf
sed -i "s/CACHE_DISK_SIZE/${CACHE_DISK_SIZE}/" /etc/nginx/conf.d/20_proxy_cache_path.conf
sed -i "s/CACHE_MAX_AGE/${CACHE_MAX_AGE}/"    /etc/nginx/sites-available/generic.conf.d/root/20_cache.conf
sed -i "s/UPSTREAM_DNS/${UPSTREAM_DNS}/"    /etc/nginx/sites-available/generic.conf.d/10_generic.conf

$PRX_PATH/scripts/update-domain-maps.sh >> $LOGFILE 2>&1

chown -R nginx:nginx /data/

systemctl enable nginx.service >> $LOGFILE 2>&1
systemctl start nginx.service >> $LOGFILE 2>&1
#eof
