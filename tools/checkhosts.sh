#!/bin/bash
# https://github.com/racaljk/hosts

LINE_BREAK=0
FORMAT_BREAK=0
DATE_BREAK=0

chk_eol()
{
	echo -e " * Check line endings:\n"

	if file "$1" | grep -q "CRLF"; then
		echo -e "\033[41mDOS line endings have appeared, " \
			"it must be coverted now!\033[0m\n\n"
		LINE_BREAK=1
	else
		echo -e "\033[42mAll is well!\033[0m\n\n"
	fi
}

# Check TAB on hosts records.
# Check leading and trailing whitespace.
#
chk_format()
{
	echo -e " * Check hosts format:\n"

	# Filter all hosts records.
	cat "$1" | grep -Pv "^\s*#" | grep -P "(\d+\.){3}\d+" > 1.swp
	# Trailing whitespace detection.
	grep -P "[ \t]+$" "$1" >> 1.swp
	# Filter good format hosts records.
	cat "$1" | grep -Pv "^\s*#" | grep -P "^(\d+\.){3}\d+\t\w" > 2.swp

	if ! diff 1.swp 2.swp > 0.swp; then
		echo -e "\033[41mhosts format mismatch! " \
			"The following rules should be normalized:\033[0m"
		cat 0.swp
		FORMAT_BREAK=1
	else
		echo -e "\033[42mAll is well!\033[0m"
	fi

	echo -e "\n"
	rm -f 0.swp 1.swp 2.swp
}

chk_date()
{
	# system date
	local real_date=$(date +%F)
	# The last change of the hosts file.
	local repo_date=$(git log --date=short "$1" | grep -Pom1 "\d+-\d+-\d+")
	# date string in hosts file.
	local hosts_date=$(grep -Po "\d+-\d+-\d+" "$1")

	echo -e " * Check hosts date:\n"

	# check if hosts file changes
	if git diff --exit-code "$1" &> /dev/null; then
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

	exit $(( $LINE_BREAK + $FORMAT_BREAK + $DATE_BREAK ))
}

if [ -z "$1" ]; then
	echo "Usage: $0 [hosts-file]"
	exit 4
fi

chk_eol "$1"
chk_format "$1"
chk_date "$1"

result
