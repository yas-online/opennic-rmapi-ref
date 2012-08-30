CC=gcc

rm_api: rm_api.c
	tcc -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_DISABLE_LFS -DSQLITE_THREADSAFE=0 -o rm_api.cgi rm_api.c libcgi.a

optimised: rm_api.c
	$(CC) -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_DISABLE_LFS -DSQLITE_THREADSAFE=0 -Os -ansi -o rm_api.cgi rm_api.c libcgi.a

debug: rm_api.c
	$(CC) -g -DDEBUG -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_DISABLE_LFS -DSQLITE_THREADSAFE=0 -ansi -o rm_api.cgi rm_api.c libcgi.a -Wl,-export-dynamic
	
clean:
	rm rm_api.cgi
