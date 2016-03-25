#!/bin/sh
#
# script_tool_for_osx
#
# Using command: `sudo sh script_tool_for_osx.sh` or
#                `su -c 'sh script_tool_for_osx.sh'`
# to update your hosts file.
#
# Or you can create a `sudo crontab job` to update your hosts file regularly.
#     1. `sudo crontab -e`
#     2. `00 09 * * * /bin/bash /path_to_hosts/hosts_tools/scripts/script_tool_for_osx.sh`
#
# Enjoy. φ(≧ω≦*)♪
#
#
# @WARNING: the script CAN NOT replace other hosts rules.
#           If you have others provided hosts rules, maybe get conflict.
#
if [ `id -u` -eq 0 ]; then
    wget 'https://raw.githubusercontent.com/racaljk/hosts/master/hosts' -O /tmp/fetchedhosts
    sed -i '/# Copyright (c) 2014/,/# Modified hosts end/d' /etc/hosts

    sed -i '/127.0.0.1/d' /etc/hosts
    echo "127.0.0.1 $(hostname)" >> /etc/hosts

    cat /tmp/fetchedhosts >> /etc/hosts
    rm -f /tmp/fetchedhosts

    echo 'Success.'
else
    echo 'Permission denied, are you root?'
fi
