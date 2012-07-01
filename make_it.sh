#!/bin/sh
# Simple compilation script.

if [ -f rm_api.cgi ]
then
echo "Removing previous copy"
rm rm_api.cgi
fi
gcc -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_DISABLE_LFS -DSQLITE_THREADSAFE=0 -o rm_api.cgi rm_api.c libcgi.a
