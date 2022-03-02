echo "### Setting up DOCKER basic components"

dnf -y config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo >> $LOGFILE 2>&1
pip install docker >> $LOGFILE 2>&1
dnf -y install docker-ce cockpit-docker httpd-tools >> $LOGFILE 2>&1

systemctl enable docker.service >> $LOGFILE 2>&1
systemctl start docker.service >> $LOGFILE 2>&1

# deploy portainer container
PASS=`htpasswd -nb -B admin $PORTAINER_PW | cut -d ":" -f 2`

docker volume create portainer_data >> $LOGFILE 2>&1
docker run -d -p 9000:9000 -p 8000:8000 --name portainer --restart always \
           -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer \
           --admin-password=$PASS \
           --templates https://bitbucket.org/apetomate/portainer-templates/raw/master/templates.json >> $LOGFILE 2>&1
#eof
