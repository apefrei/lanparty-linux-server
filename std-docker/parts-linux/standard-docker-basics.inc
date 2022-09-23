echo "### Setting up DOCKER basic components"

dnf -y config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo >> $LOGFILE 2>&1
dnf update -y >> $LOGFILE 2>&1
dnf -y install docker-ce >> $LOGFILE 2>&1

systemctl enable docker.service >> $LOGFILE 2>&1
systemctl start docker.service >> $LOGFILE 2>&1

echo "### Setting up PORTAINER for docker management"

if [ "$USE_REVERSE_PROXY" == "yes" ]
then
    docker run --detach --publish 80:80 --publish 443:443 --name nginx-proxy \
        -v certs:/etc/nginx/certs \
        -v vhost:/etc/nginx/vhost.d \
        -v html:/usr/share/nginx/html \
        -v /var/run/docker.sock:/tmp/docker.sock:ro jwilder/nginx-proxy >> $LOGFILE 2>&1

    docker run --detach --name nginx-proxy-acme \
        --volumes-from nginx-proxy \
        --volume /var/run/docker.sock:/var/run/docker.sock:ro \
        --volume acme:/etc/acme.sh \
        --env "DEFAULT_EMAIL=$LETSENCRYPT_EMAIL" nginxproxy/acme-companion >> $LOGFILE 2>&1

    docker volume create portainer_data >> $LOGFILE 2>&1
    docker run --detach --name portainer --restart always --privileged \
        --env "VIRTUAL_HOST=$PORTAINER_VHOSTNAME" --env "VIRTUAL_PORT=9000" \
        --env "LETSENCRYPT_HOST=$PORTAINER_VHOSTNAME" \
        --volume /var/run/docker.sock:/var/run/docker.sock \
        --volume portainer_data:/data portainer/portainer-ce:latest >> $LOGFILE 2>&1
else
    docker volume create portainer_data >> $LOGFILE 2>&1
    docker run -d -p 9443:9443 -p 8000:8000 --name portainer --restart always --privileged \
           -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer-ce >> $LOGFILE 2>&1
fi
#eof
