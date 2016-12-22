#!/bin/bash
# https://github.com/racaljk/hosts

LINE_BREAK=0
FORMAT_BREAK=0
DATE_BREAK=0

chk_eol()
{
	printf "\e[33;1mCheck line endings:\e[0m\n"

	if file "$1" | grep -q "CRLF"; then
		printf "\e[31mDOS line endings have appeared, "
		printf "it must be coverted now!\e[0m\n\n"
		LINE_BREAK=1
	else
		printf "\e[32mAll is well!\e[0m\n\n"
	fi
}

# Check TAB, leading and trailing whitespace.
chk_format()
{
	printf "\e[33;1mCheck hosts format:\e[0m\n"

	# Filter all hosts records.
	cat "$1" | grep -Pv "^\s*#" | grep -P "(\d+\.){3}\d+" > 1.swp
	# Trailing whitespace detection.
	grep -P "[ \t]+$" "$1" >> 1.swp
	# Filter good records.
	cat "$1" | grep -Pv "^\s*#" | grep -P "^(\d+\.){3}\d+\t\w" > 2.swp

	if ! diff 1.swp 2.swp > 0.swp; then
		printf "\e[31mhosts format mismatch! "
		printf "The following rules should be normalized:\e[0m\n"
		cat 0.swp; printf "\n"
		FORMAT_BREAK=1
	else
		printf "\e[32mAll is well!\e[0m\n\n"
	fi

	rm -f 0.swp 1.swp 2.swp
}

chk_date()
{
	local sys_date=$(date +%F)
	local repo_date=$(git log --date=short "$1" |
					grep -Pom1 "\d{4}-\d{2}-\d{2}")
	local in_file=$(grep -Po "\d{4}-\d{2}-\d{2}" "$1")

	printf "\e[33;1mCheck hosts date:\e[0m\n"

	# check if hosts file changes.
	if git diff --exit-code "$1" &> /dev/null; then
		# hosts file is not changed.
		if [ "$repo_date" != "$in_file" ]; then
			printf "\e[31mhosts date mismatch, last modified "
			printf "is ${repo_date}, but hosts tells "
			printf "${in_file}\e[0m\n\n"
			DATE_BREAK=1
		else
			printf "\e[32mAll is well!\e[0m\n\n"
		fi
	else
		# hosts file is being editing, and has not been committed.
		if [ "$sys_date" != "$in_file" ]; then
			printf "\e[31mhosts date mismatch, last modified "
			printf "is $sys_date, but hosts tells "
			printf "$in_file\e[0m\n\n"
			DATE_BREAK=1
		else
			printf "\e[32mAll is well!\e[0m\n\n"
		fi
	fi
}

if [ -z "$1" ]; then
	echo "Usage: $0 [file]"
	exit 4
fi

chk_eol "$1"
chk_format "$1"
chk_date "$1"

exit $(( $LINE_BREAK + $FORMAT_BREAK + $DATE_BREAK ))
