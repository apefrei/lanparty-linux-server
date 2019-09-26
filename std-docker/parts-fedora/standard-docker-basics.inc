echo "### Setting up DOCKER basic components"

dnf -y config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo
pip install docker
dnf -y install docker-ce cockpit-docker >> $LOGFILE 2>&1

systemctl restart nginx.service >> $LOGFILE 2>&1
#eof
