#!/bin/sh
# Simple compilation script.
# By Martin COLEMAN. Public Domain, or equivalent in your jurisdiction.

if [ -f rm_api.cgi ]
then
echo "Removing previous copy"
rm rm_api.cgi
fi
#gcc -m32 -mtune=i386 -march=i386 -o deskctrl.cgi main.c cgilib/.libs/libcgi.a
gcc -O2 -o rm_api.cgi rm_api.c libcgi.a -lsqlite3
