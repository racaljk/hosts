#!/bin/bash
#
# lhosts: update your hosts file from https://github.com/racaljk/hosts
#

myname=${0##*/}

HOSTS="/etc/hosts"
BACKUP_FILE="/etc/hosts.bak"
REMOTE_FILE="/tmp/hosts.rmt"

MAIN="https://raw.githubusercontent.com/racaljk/hosts/master/hosts"
MIRROR="https://coding.net/u/scaffrey/p/hosts/git/raw/master/hosts"
HOSTS_URL="$MAIN"

NET_TOOLS="curl"
QWGET=
QCURL=

usage()
{
	cat <<EOL
注:
  可以使用 crontab 定时执行脚本 (root 身份运行或 sudo 无需输入密码)
  更新前，原 hosts 备份至 $BACKUP_FILE

用法: $myname [选项]...

选项:
  -w, --wget             使用 wget 下载
  -m, --mirror           从镜像地址获取 hosts
  -q, --quiet            静默模式
  -u, --url <url>        自定义 hosts 源地址
  -h, -1, --help         显示帮助信息并退出

退出状态：
  0  正常
  1  命令行参数错误
  2  文件下载失败

参考:

    $myname -mq

自定义源：

    $myname -qu $MIRROR

EOL
}

get_hosts()
{
	# If the quiet mode is turned off, print some messages.
	if [ -z "$QCURL" ]; then
		echo "正在更新 hosts..."
        fi

	if [ "$NET_TOOLS" = "wget" ]; then
		# Use Wget to download.
		"$NET_TOOLS" $QWGET "$HOSTS_URL" -O "$REMOTE_FILE"
	else
		# Use cURL to download.
		"$NET_TOOLS" $QCURL "$HOSTS_URL" -#o "$REMOTE_FILE"
	fi

	if [ $? -ne 0 ]; then
		echo "hosts 下载失败" >&2
		exit 2
	fi
}

backup_hosts()
{
	sudo cp -f "$HOSTS" "$BACKUP_FILE"
}

update_hosts()
{
	local swp="/tmp/hosts.swp"
	local begin_mark="# Copyright (c) 2014"
	local end_mark="# Modified hosts end"

	# Reserved host name rules.
	grep -m 1 $(hostname) "$HOSTS" > "$swp"

	# If racaljk hosts has used, clean racaljk hosts up, and retain
	# the rest of the hosts rules.
	#
	# If not, entire hosts file will be clean up, you should get back
	# some rules from the backup files on demand.
	#
	if grep -q "racaljk" "$HOSTS"; then
		sed "/$begin_mark/,/$end_mark/d" "$HOSTS" >> "$swp"
	fi

	cat "$REMOTE_FILE" >> "$swp"
	sudo cp -f "$swp" "$HOSTS"

	rm -f "$swp" "$REMOTE_FILE"
}

LONGOPTS="wget,mirror,quiet,url:,help"
CMD=$(getopt -o wmqu:h1 --long $LONGOPTS -n "$myname" -- "$@") || exit 1

eval set -- "$CMD"

while true; do
	case "$1" in
		-w|--wget)
		NET_TOOLS="wget"
		shift
		;;
		-m|--mirror)
		HOSTS_URL="$MIRROR"
		shift
		;;
		-q|--quiet)
		QWGET=-q
		QCURL=-s
		shift
		;;
		-u|--url)
		HOSTS_URL="$2"
		shift 2
		;;
		-h|-1|--help)
		usage
		exit 0
		shift
		;;
		--)
		shift
		break
		;;
	esac
done

get_hosts
backup_hosts
update_hosts
