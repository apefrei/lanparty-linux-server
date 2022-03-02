echo "### Installing latest LT Kernel"
if [ "$INSTALL_LTKERNEL" == "yes" ]
then
    dnf -y --enablerepo=elrepo-kernel install kernel-lt >> $LOGFILE 2>&1
fi
#eof