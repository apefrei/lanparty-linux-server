```shell
______ _   _ _____ _____ ___________ _       ___   _   _
| ___ \ | | |_   _|_   _|  ___| ___ \ |     / _ \ | \ | |
| |_/ / | | | | |   | | | |__ | |_/ / |    / /_\ \|  \| |
| ___ \ | | | | |   | | |  __||    /| |    |  _  || . ` |
| |_/ / |_| | | |   | | | |___| |\ \| |____| | | || |\  |
\____/ \___/  \_/   \_/ \____/\_| \_\_____/\_| |_/\_| \_/
```
## What is this for?

* Simple Standard Fedora Linux Installation
* Less Simple Service Components for LAN Party Servers

## Install
##### 1) Create config file
echo "ENABLE_TELEGRAF=yes" > /root/.lxcfg
echo "INFLUX_IP=192.168.88.8" >> /root/.lxcfg
echo "INFLUX_ADMIN=dbadmin" >> /root/.lxcfg
echo "INFLUX_PW=<password>" >> /root/.lxcfg
##### 2) Kickstart the installation
```shell
bash <(curl -s https://bitbucket.org/apetomate/blan-standard-linux/raw/master/kickstart-butterlan-linux.sh)
```
## Components
### Nginx High-Performance Proxy Cache for Game-Downloaders
Automated installation of NGINX and all required components and configurations
##### 1) Requirements
* Fedora 30 Linux Server Edition
* Two additional storages mounted at /data/storage1 and /data/storage2, for hash-split Nginx caching
* Fixed IP-Address
##### 2) Configuration
* Change variables to your needs: /root/scripts/blan/std-proxy-cache/butterlan-proxy-cache.sh
* CACHE_DISK_SIZE will be splitted between storage1 and storage2 (count those two together)
##### 2) Install
```shell
/root/scripts/blan/std-proxy-cache/butterlan-proxy-cache.sh
```
