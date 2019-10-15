echo "### Chose your Gameserver"
echo
echo 'What gameserver would you like to install?'
echo 'You'll find the list here: https://github.com/GameServerManagers/LinuxGSM/blob/master/lgsm/data/serverlist.csv'
echo 'Get your Steamserver-Token here: https://steamcommunity.com/dev/managegameservers'
echo 'Example: "${green}csgoserver${nc}" - Counter-Strike: Global Offensive'
echo 'Example: "${green}fctrserver${nc}" - Factorio'
echo 'Example: "${green}mcserver${nc}" - Minecraft'
read -p 'Gameserver: ' GAMESERVER

TEMP_PATH=$(mktemp -d)
cd $TEMP_PATH
wget https://raw.githubusercontent.com/GameServerManagers/LinuxGSM/master/lgsm/data/serverlist.csv
available_server=$( tail -n +2 "serverlist.csv" | awk -F "," '{print $2}' )

if
  grep -qw $GAMESERVER <<< $available_server
then
  echo
  echo
  echo "Good choice! We're now proceeding with creating the $GAMESERVER environment"
else
  echo "This Gameserver cannot be found"
  echo "Please recheck the list of possible choices: https://github.com/GameServerManagers/LinuxGSM/blob/master/lgsm/data/serverlist.csv"
  exit 1
fi

#cleanup
cd $GSM_PATH
rm -rf $TEMP_PATH

#create user environment
adduser $GAMESERVER
THEPASS="`xkcdpass $XKCDOPTS`"
echo "$THEPASS" | passwd --stdin "$GAMESERVER"
passwordInfo "Gameserver-$GAMESERVER" ""$GAMESERVER" ""$THEPASS"

#create runscript
available_server_name=$( tail -n +2 "serverlist.csv" | awk -F "," '{print $3}' )
SCRIPTPATH=/etc/systemd/system/$GAMESERVER.service
cp $GSM_PATH/configs-fedora/GAMESERVER.service $SCRIPTPATH

GSMDESCRIPTION=$available_server_name
GSMUSER=$GAMESERVER
GSMDIR=$GAMESERVER
GSMSCRIPT=$GAMESERVER

set -e
sed -i "s/GSMDESCRIPTION/${GSMDESCRIPTION}/" $SCRIPTPATH
sed -i "s/GSMUSER/${GSMUSER}/" $SCRIPTPATH
sed -i "s/GSMDIR/${GSMDIR}/" $SCRIPTPATH
sed -i "s/GSMSCRIPT/${GSMSCRIPT}/" $SCRIPTPATH


USRHOME=/home/$GAMESERVER
cd $USRHOME
#sudo -u $GAMESERVER wget -O $USRHOME/linuxgsm.sh https://linuxgsm.sh
#sudo -u $GAMESERVER chmod +x $USRHOME/linuxgsm.sh
#sudo -u $GAMESERVER $USRHOME/linuxgsm.sh $GAMESERVER
#sudo -u $GAMESERVER $USRHOME/$GAMESERVER install
#https://linuxgsm.com/lgsm/csgoserver/
