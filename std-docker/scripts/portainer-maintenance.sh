# #!/bin/bash
#
# Prune all unused images and update Portainer to latest
#
docker image prune -a -f
docker stop portainer
docker rm portainer
docker pull portainer/portainer-ce:latest

docker run -d -p 9443:9443 -p 8000:8000 --name portainer --restart always \
           -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer-ce \
           --templates https://bitbucket.org/apetomate/portainer-templates/raw/master/templates.json
