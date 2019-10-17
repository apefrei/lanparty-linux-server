echo "### Chose your Gameserver"
echo
echo "What gameserver would you like to install?"
echo
echo "You'll find the list here: https://github.com/GameServerManagers/LinuxGSM/blob/master/lgsm/data/serverlist.csv"
echo "Get your Steamserver-Token here: https://steamcommunity.com/dev/managegameservers"
echo
echo -e "Example: ${green}csgoserver${nc} - Counter-Strike: Global Offensive"
echo -e "Example: ${green}fctrserver${nc} - Factorio"
echo -e "Example: "${green}mcserver${nc}" - Minecraft"
echo
read -p "Gameserver: " GAMESERVER

TEMP_PATH=$(mktemp -d)
cd $TEMP_PATH
wget https://raw.githubusercontent.com/GameServerManagers/LinuxGSM/master/lgsm/data/serverlist.csv  >> $LOGFILE 2>&1
available_server=$( tail -n +2 "serverlist.csv" | awk -F "," '{print $2}' )

if
  grep -qw $GAMESERVER <<< $available_server
then
  echo
  echo
  echo -e "Good choice! We're now proceeding with creating the ${green}$GAMESERVER${nc} environment"
else
  echo -e "This Gameserver ${red}cannot be found${nc}"
  echo "Please recheck the list of possible choices: https://github.com/GameServerManagers/LinuxGSM/blob/master/lgsm/data/serverlist.csv"
  exit 1
fi

#cleanup
cd $GSM_PATH
rm -rf $TEMP_PATH

adduser $GAMESERVER  >> $LOGFILE 2>&1
THEPASS="`apg $APGOPTS`"  >> $LOGFILE 2>&1
echo "$THEPASS" | passwd --stdin "$GAMESERVER"  >> $LOGFILE 2>&1

USRHOME=/home/$GAMESERVER
cd $USRHOME
sudo -u $GAMESERVER wget -O $USRHOME/linuxgsm.sh https://linuxgsm.sh  >> $LOGFILE 2>&1
sudo -u $GAMESERVER chmod +x $USRHOME/linuxgsm.sh  >> $LOGFILE 2>&1
sudo -u $GAMESERVER $USRHOME/linuxgsm.sh $GAMESERVER  >> $LOGFILE 2>&1
sudo -u $GAMESERVER $USRHOME/$GAMESERVER install

echo
passwordInfo "GAMESERVER: $GAMESERVER" "$GAMESERVER" "$THEPASS"
