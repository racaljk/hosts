#!/bin/sh
site=https://github.com/racaljk/hosts

thisname=${0##*/}

HOSTS=/etc/hosts
REMOTE="/tmp/hosts.rmt"

MAIN="https://raw.githubusercontent.com/racaljk/hosts/master/hosts"
MIRROR="https://coding.net/u/scaffrey/p/hosts/git/raw/master/hosts"
HOSTS_URL="$MAIN"

NET_TOOL="curl"
QWGET=
QCURL=

usage() {
    cat >&2 <<EOL
提示:
  可使用 crontab 定时执行脚本 (请确保 sudo 无需输入密码)

用法: $thisname [选项]...
默认从 $site 获取 hosts 文件 (更新文件内 localhost 为 `hostname`)
替换到 $HOSTS 中。更新前备份原 hosts 至 /etc/hosts.bak

选项:
  -w, --wget             使用 wget 下载
  -m, --mirror           使用 hosts 镜像地址
  -q, --quiet            静默模式
  -u, --url              自定义 hosts 源地址
  -h, -1, --help         显示帮助信息并退出

退出状态：
  0  正常
  1  一般问题 (例如：命令行参数错误)
  2  严重问题 (例如：文件下载失败)

参考:

    $thisname -mq

自定义源：

    $thisname -qu $MIRROR

EOL
}

hosts_get() {
    if [ "$NET_TOOL" = "wget" ]; then
        "$NET_TOOL" $QWGET "$HOSTS_URL" -O "$REMOTE"
    else
        # use curl
    if [ "$QCURL" = "" ]; then
        echo "正在更新 hosts ..."
    fi
        "$NET_TOOL" -# $QCURL "$HOSTS_URL" -o "$REMOTE"
    fi

    if [ "$?" -ne 0 ]; then
        echo -e "\nhosts 下载失败" >&2
        exit 2
    fi
}

hosts_update() {
    local old="$1"
    local rmt="$2"
    local tmp="/tmp/hosts.swp"
    local bak="/etc/hosts.bak"
    local begin="# Copyright (c) 2014"
    local end="# Modified hosts end"

    sed -e "s/localhost/`hostname`/g" "$rmt" > "$tmp"
    rm -f "$rmt"

    # check if racaljk hosts, or do nothing
    if grep -q racaljk "$old"; then
        sed -e "/$begin/,/$end/d" "$old" >> "$tmp"
    fi

    sudo cp "$old" "$bak"
    cat "$tmp" | sudo tee "$old" > /dev/null
}

CMD=`getopt -o wmqu:h1 --long wget,mirror,quiet,url:help -n \
    "$thisname" -- "$@"` || exit 1

eval set -- "$CMD"

while true; do
    case "$1" in
        -w|--wget)
            NET_TOOL="wget"
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

hosts_get
hosts_update "$HOSTS" "$REMOTE"
