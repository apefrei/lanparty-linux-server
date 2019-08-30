#!/bin/bash
#
# Script to run after /etc/default/grub has been modified
#

cp -a /boot/grub2/grub.cfg{,.orig}
grub2-mkconfig -o /boot/grub2/grub.cfg

# eof