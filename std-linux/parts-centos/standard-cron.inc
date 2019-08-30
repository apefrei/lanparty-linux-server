echo "### Setting up cron"
sed -r -i "s/(^MAILTO=).*$/\1$ADMIN_EMAIL/g" /etc/crontab

# eof
