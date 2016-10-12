#!/bin/bash
# https://github.com/racaljk/hosts

LINE_BREAK=0
FORMAT_BREAK=0
DATE_BREAK=0

chk_eol()
{
	echo -e "- Check line endings:\n"

	if file "$1" | grep "CRLF" -q; then
		echo -e "\033[41mDOS line endings have appeared, " \
			"it must be coverted now!\033[0m\n\n"
		LINE_BREAK=1
	else
		echo -e "\033[42mAll is well!\033[0m\n\n"
	fi
}

chk_format()
{
	echo -e "- Check hosts format:\n"

	grep -P "\d+\.\d+\.\d+\.\d+" "$1" > 1.txt
	grep -P "\d+\.\d+\.\d+\.\d+\t\w+" "$1" > 2.txt

	if ! diff 1.txt 2.txt > 0.txt; then
		echo -e "\n\033[41mhosts format mismatch! " \
			"The following rules should be normalized:\033[0m"
		cat 0.txt
		FORMAT_BREAK=1
	else
		echo -e "\033[42mAll is well!\033[0m"
	fi

	echo -e "\n"
	rm -f 0.txt 1.txt 2.txt
}

chk_date()
{
	# get the system date
	local real_date=$(date +%F)
	# get the hosts last modified in git log records
	local repo_date=$(git log --date=short "$1" | grep -Pom1 "\d+-\d+-\d+")
	# date string in hosts file.
	local hosts_date=$(grep -Po "\d+-\d+-\d+" "$1")

	echo -e "- Check hosts date:\n"

	# check if hosts file changes
	if git diff --exit-code "$1" > /dev/null 2>&1; then
		# hosts file is not changed, compare file's date with git log.
		if [ "$repo_date" != "$hosts_date" ]; then
			echo -e "\033[41mhosts date mismatch, last modified " \
				"is $repo_date, but hosts tells " \
				"$hosts_date\033[0m\n\n"
			DATE_BREAK=1
		else
			echo -e "\033[42mAll is well!\033[0m\n\n"
		fi
	else
		# hosts file is being editing, and has not been committed.
		# Compare file's date with the system date.
		if [ "$real_date" != "$hosts_date" ]; then
			echo -e "\033[41mhosts date mismatch, last modified " \
				"is $real_date, but hosts tells " \
				"$hosts_date\033[0m\n\n"
			DATE_BREAK=1
		else
			echo -e "\033[42mAll is well!\033[0m\n\n"
		fi
	fi
}

result()
{
	echo -e "Result (1 = yes, 0 = no):\n"
	echo "line endings break?      [ $LINE_BREAK ]"
	echo "hosts format mismatch?   [ $FORMAT_BREAK ]"
	echo "hosts date mismatch?     [ $DATE_BREAK ]"

	local ret=$(expr $LINE_BREAK + $FORMAT_BREAK + $DATE_BREAK)
	exit $ret
}

if [ -z "$1" ]; then
	echo "Usage: $0 [your-hosts-file]"
	exit 1
fi

chk_eol "$1"
chk_format "$1"
chk_date "$1"

result
