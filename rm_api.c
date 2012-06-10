/*
	Remote Management API
	For the OpenNIC Project.
	By Martin COLEMAN (C) 2012. All rights reserved.
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; version 2 of the License only.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software Foundation
	Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

	------------
	All test code. Do not use unless you know what you are doing!!
	------------
	CMDS: check, register, update, transfer, delete, assist
*/
#include <sqlite3.h>
#include <stdio.h>
#include "cgi.h"
#define TESTING

/* for SQLite3 */
sqlite3 *db;
sqlite3_stmt *res;
char *zErrMsg=0;
int rc;

/* for cgilib */
s_cgi *cgi;

void notify(int result)
{
	printf("Content-type: text/html\n\n");
	printf("%d", result);
}

int verify(char user[10], char key[16])
{
	return 1;
}

int domain_exists(char domain[50])
{
	return 0;
}

int register_domain(char domain[50], char name[20], char email[50], char ns1[50], char ns2[50])
{
	#ifndef TESTING
	rc = sqlite3_open("OZ_tld.sq3", &db);
	if(rc)
	{
		fprintf(stderr, "Can't open domain database.\n");
		sqlite3_close(db);
		return 0;
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
	#endif
	return 1;
}

int get_support(char tld[5])
{
}

int main(void)
{
	char *cmd;
	char *user;
	char *userkey;
	char *domain;
	char *name;
	char *email;
	char *ns1;
	char *ns2;
	char *tld;
	int rc=0;
	cgi = cgiInit();

	if(cmd=cgiGetValue(cgi, "cmd"))
	{
		if(!strcmp(cmd, "check"))
		{
			user=cgiGetValue(cgi, "user");
			userkey=cgiGetValue(cgi, "userkey");
			domain=cgiGetValue(cgi, "domain");
			if(verify(user, userkey))
			{
				rc=domain_exists(domain);
				notify(rc);
			} else {
				notify(255);
			}
			return 0;
		} else if(!strcmp(cmd, "record"))
		{
			user=cgiGetValue(cgi, "user");
			userkey=cgiGetValue(cgi, "userkey");
			domain=cgiGetValue(cgi, "domain");
			name=cgiGetValue(cgi, "name");
			email=cgiGetValue(cgi, "email");
			ns1=cgiGetValue(cgi, "ns1");
			ns2=cgiGetValue(cgi, "ns2");
			/* verify user and key */
			if(verify(user, userkey))
			{
				rc=register_domain(domain, name, email, ns1, ns2);
				notify(rc);
			} else {
				notify(255);
			}
			return 0;
		} else if(!strcmp(cmd, "assist"))
		{
			/* request for assistance. this will go directly to the TLD manager */
			user=cgiGetValue(cgi, "user");
			userkey=cgiGetValue(cgi, "userkey");
			tld=cgiGetValue(cgi, "tld");
			if(verify(user, key))
			{
				rc=get_support(tld);
				notify(rc);
			} else {
				notify(255);
			}
		}
	} else {
		printf("Content-type: text/html\n\n");
		printf("Unrecognised request.\n\n");
		return 0;
	}
	return 0;
}
