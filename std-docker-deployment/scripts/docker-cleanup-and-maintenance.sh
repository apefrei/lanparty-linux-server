#!/bin/sh
#
# Prune all unused images and update Portainer to latest
#
docker image prune -a -f
docker container kill portainer
docker container rm portainer
docker image rm portainer/portainer

# get primary ip
# ip=$(ifconfig eth0 | awk '/inet addr/{print substr($2,6)}')
ip=$(ip addr show eth0 | grep "inet\b" | awk '{print $2}' | cut -d/ -f1)

###
docker run -d \
    -p $ip:9000:9000 \
    --restart always \
    --name portainer \
    -v /var/run/docker.sock:/var/run/docker.sock \
    -v portainer_data:/data \
    portainer/portainer:latest
