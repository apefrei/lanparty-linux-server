## What's this for?

* Simple Standard CentOS Linux Installation, with basic tools
* Service Components for LAN Party Servers

## Inspiration

This project is inspired by the work of "https://github.com/lancachenet" and "https://github.com/uklans"

* Elements of those script are taken from the "https://github.com/lancachenet" project
* The cache domains are maintained by the "https://github.com/uklans" project

## Important

* Those scripts are in no way enhancing your linux hosts security in any way. on the contrary!
* Tested on CentOS 8

## Install
##### 1) Requirements
* CentOS 8 **Server** Installation
* Fixed IP-Address(es)
##### 2) Configuration
```shell
echo "ENABLE_TELEGRAF=no" > /root/.stdcfg
echo "ENABLE_COCKPIT=yes" >> /root/.stdcfg
echo "INSTALL_LTKERNEL=yes" >> /root.stdcfg
echo "INFLUX_IP=192.168.88.8" >> /root/.stdcfg
echo "INFLUX_ADMIN=dbadmin" >> /root/.stdcfg
echo "INFLUX_PW=yourpass" >> /root/.stdcfg
```
* If you do not use stat collecting by influxdb, set ENABLE_TELEGRAF=no. You can enable the service later
* ENABLE_COCKPIT will enable, the already installed, cockpit web-management service
* INFLUX_IP will be the timeseries database you send your metrics to
##### 3) Kickstart the installation
```shell
bash <(curl -s https://bitbucket.org/apetomate/lanparty-standard-linux/raw/master/kickstart-lanparty-linux.sh)
```
## Components
### [A] Nginx High-Performance Proxy Cache for Game-Download-Clients (Steam, Epic Store, ...)
Automated installation of NGINX and all required components and configurations
##### 1) Requirements
* CentOS 8 **Server** Installation
* Bootstrapped with Kickstart Script
* Two additional storages mounted at /data/storage1 and /data/storage2, for hash-split Nginx caching
* Fixed IP-Address(es)
##### 2) Configuration
```shell
echo 'CACHE_MEM_SIZE="2000m"' > /root/.prxcfg
echo 'CACHE_DISK_SIZE="1700000m"' >> /root/.prxcfg
echo 'CACHE_MAX_AGE="3560d"' >> /root/.prxcfg
echo 'UPSTREAM_DNS="192.168.88.1"' >> /root/.prxcfg
echo 'LOGFILE_RETENTION="3560"' >> /root/.prxcfg
echo 'NGINX_WORKER_PROCESSES="auto"' >> /root/.prxcfg
```
* CACHE_MEM_SIZE is the keys_zone memory cache only (do not allocate all your RAM)
* CACHE_DISK_SIZE will be splitted between storage1 and storage2 (count those two together)
##### 3) Install
```shell
/root/scripts/lanparty/std-proxy-cache/lanparty-proxy-cache.sh
```
### [B] Standard Docker Environment with Butterlan Templates
Automated installation of DOCKER and PORTAINER with Butterlan Templates
##### 1) Requirements
* CentOS 8 **Server** Installation
* Bootstrapped with Kickstart Script
* Fixed IP-Address(es)
##### 2) Configuration
```shell
echo 'PORTAINER_PW="password"' > /root/.dkrcfg
```
##### 3) Install
```shell
/root/scripts/lanparty/std-docker/lanparty-docker.sh
```
### [C] Standard LinuxGSM Environment
Automated building of LinuxGSM environment for all gameservers (only tested on cs:go and cs:source)
##### 1) Requirements
* CentOS 8 **Server** Installation
* Bootstrapped with Kickstart Script
* Fixed IP-Address(es)
##### 2) Configuration
There is no pre configuration. Therefore, the script depends on your userinput.
##### 3) Install
```shell
/root/scripts/lanparty/std-linuxgsm/lanparty-linuxgsm.sh
```
