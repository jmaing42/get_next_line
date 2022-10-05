#!/bin/sh

set -e

FILE_NAME="fake_file_name (file name is useless too)    "
# FILE_NAME="$(basename $1)$(printf %45.45s)" # uncomment when norminette starts complain it
PLACEHOLDER="PLACEHOLDER_FOR_FILE_NAME_UP_TO_45_CHARACTERS"

if [ "$( < "$1" tr -d '\n' | grep -Ec \\/\\\*\ \\\*\{74\}\ \\\*\\/\\/\\\*.\*\\\*\\/\\/\\\*.\*\\\*\\/\\/\\\*.\{3\}\(\[\^\ \]\*\).\*\\\*\\/\\/\\\*.\*\\\*\\/\\/\\\*\ \ \ By:\ \(\[\^\ \]\*\).\*\\\*\\/\\/\\\*.\*\\\*\\/\\/\\\*\ \ \ Created:\ \(\[\^\ \]\*\ \[\^\ \]\*\)\ by\ \(\[\^\ \]\*\).\*\\\*\\/\\/\\\*\ \ \ Updated:\ \(\[\^\ \]\*\ \[\^\ \]\*\)\ by\ \(\[\^\ \]\*\).\*\\\*\\/\\/\\\*.\*\\\*\\/\\/\\\*\ \\\*\{74\}\ \\\*\\/)" = "1" ] ; then
  sed "s/$PLACEHOLDER/$FILE_NAME/" < hook/assets/42header-template.txt > "$1.tmp"
  tail -n +12 "$1" >> "$1.tmp"
  mv "$1" "$1.bak"
  mv "$1.tmp" "$1"
  rm -f "$1.bak"
  git add "$1"
fi
