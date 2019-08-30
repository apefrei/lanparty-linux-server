#!/bin/bash

if test -z "$1"
then
    echo "Usage: $0 <userid>"
    exit 1
fi

ps -o rss --no-headers -u $1 | awk '{ total += $0 } END { print total/NR }'

# eof
