#!/usr/bin/env bash
if [ ${UID} == 0 ]; then
    mv /etc/hosts /etc/hosts-$(date +%F-%H%M%S).bak
    wget https://raw.githubusercontent.com/racaljk/hosts/master/hosts -O fetchedhosts

	sed -i "s/localhost/localhost $(hostname)/g" fetchedhosts
	sed -i "s/broadcasthost/broadcasthost $(hostname)/g" fetchedhosts

    mv fetchedhosts /etc/hosts
    echo Success.
else
    echo permission denied, are you root?
fi
