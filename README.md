## What's this for?

* Simple Standard Rocky Linux Installation, with basic tools
* Service Components for LAN Party Servers

## Inspiration

This project is inspired by the work of "https://github.com/lancachenet" and "https://github.com/uklans"

* Elements of those script are taken from the "https://github.com/lancachenet" project
* The cache domains are maintained by the "https://github.com/uklans" project

## Important

* Those scripts are in no way enhancing your linux hosts security in any way. On the contrary!
* Tested on Rocky Linux 9

## Install
##### 1) Requirements
* **Rocky Linux 9 minimal** Installation
* Fixed IP-Address(es)
##### 2) Configuration
```shell
echo "ENABLE_TELEGRAF=no" > /root/.stdcfg
echo "ENABLE_COCKPIT=yes" >> /root/.stdcfg
#echo "INSTALL_LTKERNEL=no" >> /root/.stdcfg - with rockylinux 9, this is no longer needed
echo "INFLUX_IP=192.168.88.8" >> /root/.stdcfg
echo "INFLUX_ADMIN=dbadmin" >> /root/.stdcfg
echo "INFLUX_PW=yourpass" >> /root/.stdcfg
```
* **ENABLE_TELEGRAF** will enable sending your metrics to an influx db service. You can enable the service later
* **ENABLE_COCKPIT** will enable, the already installed, cockpit web-management service
* **INSTALL_LTKERNEL** will install the latest LT-Kernel from ELREPO (better hardware compatibility)
* **INFLUX_IP** will be the timeseries database you send your metrics to
##### 3) Kickstart the installation
```shell
bash <(curl -s https://raw.githubusercontent.com/apefrei/lanparty-linux-server/master/kickstart-lanparty-linux.sh)
```
## Components
### [A] Nginx High-Performance Proxy Cache for Game-Download-Clients (Steam, Epic Store, ...)
Automated installation of NGINX and all required components and configurations
##### 1) Requirements
* **Rocky Linux 9 minimal** Installation
* Bootstrapped with Kickstart Script
* Two additional storages mounted at /data/storage1 and /data/storage2, for hash-split Nginx caching
* Fixed IP-Address(es)
##### 2) Configuration
```shell
echo 'CACHE_INDEX_SIZE="1000m"' > /root/.prxcfg
echo 'CACHE_DISK_SIZE="1800g"' >> /root/.prxcfg
echo 'CACHE_MAX_AGE="3560d"' >> /root/.prxcfg
echo 'UPSTREAM_DNS="192.168.88.1"' >> /root/.prxcfg
echo 'LOGFILE_RETENTION="3560"' >> /root/.prxcfg
echo 'NGINX_WORKER_PROCESSES="auto"' >> /root/.prxcfg
```
* **CACHE_INDEX_SIZE** is the keys_zone memory cache only (1GB will support 4TB of diskcache easily)
* **CACHE_DISK_SIZE** will be the size of data per storage target
##### 3) Install
```shell
/root/scripts/lanparty/std-proxy-cache/lanparty-proxy-cache.sh
```
### [B] Standard Docker Environment with Butterlan Templates
Automated installation of DOCKER and PORTAINER with Butterlan Templates
##### 1) Requirements
* **Rocky Linux 9 minimal** Installation
* Bootstrapped with Kickstart Script
* Fixed IP-Address(es)
* If you set USE_REVERSE_PROXY="yes", it will always use letsencrypt and therefore the other params are mandatory
* ##### 2) Configuration
```shell
echo 'USE_REVERSE_PROXY="yes"' > /root/.dkrcfg
echo 'LETSENCRYPT_EMAIL="your@email.com"' >> /root/.dkrcfg
echo 'PORTAINER_VHOSTNAME="your.domain.com"' >> /root/.dkrcfg
```
##### 3) Install
```shell
/root/scripts/lanparty/std-docker/lanparty-docker.sh
```
### [C] Standard LinuxGSM Environment
Automated building of LinuxGSM environment for all gameservers (only tested on cs:go and cs:source)
##### 1) Requirements
* **Rocky Linux 9 minimal** Installation
* Bootstrapped with Kickstart Script
* Fixed IP-Address(es)
##### 2) Configuration
There is no pre configuration. Therefore, the script depends on your userinput.
##### 3) Install
```shell
/root/scripts/lanparty/std-linuxgsm/lanparty-linuxgsm.sh
```
