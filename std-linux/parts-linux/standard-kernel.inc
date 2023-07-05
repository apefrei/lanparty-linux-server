
if [ "$INSTALL_LTKERNEL" == "yes" ]
then
    echo "### Installing latest LT Kernel"
    dnf -y --enablerepo=elrepo-kernel install kernel-lt >> $LOGFILE 2>&1
fi
#eof