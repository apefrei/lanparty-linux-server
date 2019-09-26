# #!/bin/bash
#
# Prune all unused images and update Portainer to latest
#
docker image prune -a -f
docker container stop portainer
docker container rm portainer
docker image rm portainer/portainer

docker run -d -p 9000:9000 -p 8000:8000 --name portainer --restart always \
           -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer \
           --templates https://bitbucket.org/apetomate/portainer-templates/raw/master/templates.json
