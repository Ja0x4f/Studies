#!/bin/bash

# The '-f' flag check if the file exist
# The '-w' flag check if hte file was writable

if [ -f "$filename" ] && [ -w "$filename" ]
then
	echo "hello" > $filename
else
	touch "$filename"
	echo "hello" > $filename
fi
