#!/bin/bash
#Script Template
#This script is purposed to automaticly update hosts file from some on-line hosts-provider.
HOSTS_PATH='/etc/hosts'
REPO_URL='https://raw.githubusercontent.com/racaljk/hosts/master/hosts'
AUTO_HOSTS_MARK='###AntoHostsMark###'   #This is a separator to identify the local hosts and on-line hosts
HOSTS_BAK="$HOME/.host_create_by_`basename $0`.bak"
HOSTS_DOWNLOAD="$HOME/.host_create_by_`basename $0`.download"
HOSTS_REBUILD="$HOME/.host_create_by_`basename $0`.rebuild"

#=======Common Function Start =======
LOG_HOME="$HOME/.scripts/logs"
LOG_NAME="`basename $0`.log"
LOG_PATH="${LOG_HOME}/${LOG_NAME}"
function checkRoot
{
 if [[ `id -u` -eq 0  ]];then
	if [[ "$1" != "root" ]];then
	  echo "ERROR: \"autohosts\" CANNOT run under root."
	  exit 1
	fi
 elif [[ "$1" == "root" ]]; then
	echo "ERROR: \"autohosts\" must run under root."
	exit 1
 fi

}
function sendNotify
{
  if [[ -n "$1" ]];then
    notify-send "<`basename $0`>  $1"
  fi
}
function makeLogs
{
  if [[ ! -d "`dirname \"$LOG_PATH\"`" ]];then
     echo "ERROR: $LOG_PATH DOES NOT EXIT!"
     return
  else 
    touch "$LOG_PATH"
    if [[ -z "$LOG_PATH"  ]];then
       echo "ERROR: $LOG_PATH CANNOT BE WROTE!"
       return
    fi
  fi
  if [[ -n "$1" ]];then
      echo "[`date +%F-%T `] $1">> "$LOG_PATH"
  fi
}

function checkResult
{
	if [ $1 -eq 0 ];then
		sendNotify "$2"
		makeLogs "$2"
	else
	
		sendNotify "$3"
		makeLogs "$3"
		if [ -n "$4" ];then
		  eval "$4"
		fi
	fi

}

#=======Common Function End   =======

checkRoot
if [[ ! -w "${HOSTS_PATH}" ]];then
    echo "WARNING: $USER doesn't have WRITE-access to ${HOSTS_PATH}"
    echo "Enter root password to grant it!"
    sudo chmod +w "${HOSTS_PATH}"
    checkResult $? "" "ERROR: $USER doesn't have WRITE-access to ${HOSTS_PATH}!"\
		   "exit 1"
fi
rm -f "$HOSTS_BAK" && \
rm -f "$HOSTS_DOWNLOAD" && \
rm -f "$HOSTS_REBUILD" && \
cp -a "$HOSTS_PATH" "$HOSTS_BAK"	 && \
wget $REPO_URL -O "$HOSTS_DOWNLOAD"
checkResult $? "" "ERROR:DOWNLOAD FAILED!" \
		  "rm -f \"$HOSTS_DOWNLOAD\" \"$HOSTS_BAK\" ;exit 1"
		  
sed -n "/$AUTO_HOSTS_MARK/q;p" $HOSTS_PATH | sed -e "\$a$AUTO_HOSTS_MARK" >  "$HOSTS_REBUILD" && \
cat "$HOSTS_REBUILD" > $HOSTS_PATH && \
cat "$HOSTS_DOWNLOAD" | sed '/live.com/d' >> $HOSTS_PATH
checkResult  $?  "SUCCESS:HOSTS IS LATEST!" "ERROR:HOSTS UPDATE FAILED!" \
		  "rm -f \"$HOSTS_DOWNLOAD\" \"$HOSTS_REBUILD\";cat  \"$HOSTS_BAK\" > \"$HOSTS_PATH\";exit 1"
rm -f "$HOSTS_DOWNLOAD" "$HOSTS_REBUILD" 



# Entrance
