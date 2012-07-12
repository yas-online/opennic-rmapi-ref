/*
	Remote Management API
	For the OpenNIC Project.
	Copyright (C) 2012 Martin COLEMAN (C) 2012.
	Web: www.mchomenet.info or www.mchomenet.oz
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	------------
	All test code. Do not use unless you know what you are doing!!
	------------
	CMDS: check, register, update, transfer, delete, assist
	
	Update 2012-06-14
	- Code fixes
	- Example code now supplied (register, check)
	
	Version v0.5 - 2012-07-01
	- Embeds SQLite3
	- Improved handling of TLD
	- Supports multiple TLDs
	- Actually works now :)
	- Changed database name
	- Changed to GPL v3 license.
	- Transfer, delete and assist temporarily disabled.
	
	Version v0.51 - 2012-07-12
	- After a short break, tidied up a little bit.
*/
#include <stdio.h>
#include <time.h>
#include "sqlite3.c"
#include "cgi.h"
#define DEBUG

/* for SQLite3 */
sqlite3 *db;
sqlite3_stmt *res;
char *zErrMsg=0;
int rc;

/* for cgilib */
s_cgi *cgi;
char db_file[15]="opennic_man.sq3";

void notify(int result)
{
	cgiFree(cgi);
	printf("Content-type: text/html\n\n");
	printf("%d", result);
}

int verify(char user[10], char key[16])
{
	char sql_str[1024];
	int result=0;
	char res_user[10];
	char res_userkey[16];

	sprintf(sql_str, "SELECT r_userid FROM registrars WHERE r_user='%s' AND r_userkey='%s' LIMIT 1", user, key);
	rc = sqlite3_open(db_file, &db);
	if(rc)
	{
		printf("Can't open package database.");
		sqlite3_close(db);
		return 255;
	}
	rc = sqlite3_prepare_v2(db, sql_str, 1024, &res, 0);
	if(rc != SQLITE_OK)
	{
		printf("The package database file is corrupt!");
		sqlite3_free(zErrMsg);
		sqlite3_close(db);
		return 255;
	}
	while(1)
	{
		result=sqlite3_step(res);
		if(result==SQLITE_ROW)
		{
			sprintf(res_user, "%s", sqlite3_column_text(res, 0));
			sprintf(res_userkey, "%s", sqlite3_column_text(res, 1));
		} else {
			break;
		}
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
	if(!strcmp(res_user, user))
	{
		return 1;
	} else {
		return 0;
	}
}

int domain_exists(char tld[5], char domain[50])
{
	char sql_str[1024];
	int result=0;
	char domain_name[50];

	sprintf(sql_str, "SELECT domain FROM %s_domains WHERE domain='%s' LIMIT 1", tld, domain);
	rc = sqlite3_open(db_file, &db);
	if(rc)
	{
		printf("Can't open package database.");
		sqlite3_close(db);
		return 255;
	}
	rc = sqlite3_prepare_v2(db, sql_str, 1024, &res, 0);
	if(rc != SQLITE_OK)
	{
		printf("The package database file is corrupt!");
		sqlite3_free(zErrMsg);
		sqlite3_close(db);
		return 255;
	}
	while(1)
	{
		result=sqlite3_step(res);
		if(result==SQLITE_ROW)
		{
			sprintf(domain_name, "%s",sqlite3_column_text(res, 0));
		} else {
			break;
		}
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
	if(!strcmp(domain, domain_name))
	{
		return 1;
	} else {
		return 0;
	}
	return 255;
}

int delete_domain(char tld[5], char domain[50], char name[20], char email[50])
{
	char sql_str[1024];
	int result=0;

	sprintf(sql_str, "DELETE FROM %s_domains WHERE domain='%s', name='%s', email='%s' LIMIT 1", tld, domain, name, email);
	rc = sqlite3_open(db_file, &db);
	if(rc)
	{
		//printf("Can't open package database.");
		sqlite3_close(db);
		return 255;
	}
	rc = sqlite3_prepare_v2(db, sql_str, -1, &res, 0);
	if(rc != SQLITE_OK)
	{
		//printf("DB Error: %s\n", sqlite3_errmsg(db));
		sqlite3_free(zErrMsg);
		sqlite3_close(db);
		return 255;
	}
	while(1)
	{
		result=sqlite3_step(res);
		if(result==SQLITE_ROW)
		{
		} else {
			break;
		}
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
	return 1;
}

int register_domain(char tld[5], char domain[50], char name[20], char email[50], char ns1[50], char ns2[50])
{
	FILE *fp;
	char sql_str[1024];
	int result=0;
	char updated[11];
	time_t t;
	struct tm* tm;

	time(&t);
	tm = localtime(&t);
	strftime(updated, sizeof updated, "%Y-%m-%d", tm);

	//sql_str=sqlite3_mprintf("INSERT INTO domains (domain, name, email, ns1, ns2) VALUES('%s', '%s', '%s', '%s', '%s')", domain, name, email, ns1, ns2);
	sprintf(sql_str, "INSERT INTO %s_domains (domain, name, email, ns1, ns2, registered, expires, updated, userid) VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', 1)", tld, domain, name, email, ns1, ns2, updated, updated, updated);
	rc = sqlite3_open(db_file, &db);
	if(rc)
	{
		//printf("Can't open package database.");
		sqlite3_close(db);
		return 255;
	}
	rc = sqlite3_prepare_v2(db, sql_str, -1, &res, 0);
	if(rc != SQLITE_OK)
	{
		//printf("DB Error: %s\n", sqlite3_errmsg(db));
		sqlite3_free(zErrMsg);
		sqlite3_close(db);
		return 0;
	}
	while(1)
	{
		result=sqlite3_step(res);
		if(result==SQLITE_ROW)
		{
		} else {
			break;
		}
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
	sql_str[0]='\0';
	fp=fopen("/tmp/inittld.flag", "r");
	fprintf(fp, "1");
	fclose(fp);
	return 1;
}

int get_support(char tld[5])
{
}

int update_domain(char tld[5], char domain[50], char name[20], char email[50], char ns1[50], char ns2[50])
{
	char sql_str[1024];
	char updated[11];
	int result=0;
	time_t t;
	struct tm* tm;

	time(&t);
	tm = localtime(&t);
	strftime(updated, sizeof updated, "%Y-%m-%d", tm);

	sprintf(sql_str, "UPDATE %s_domains SET domain='%s', name='%s', email='%s', ns1='%s', ns2='%s', updated='%s';", tld, domain, name, email, ns1, ns2, updated);
	rc = sqlite3_open(db_file, &db);
	if(rc)
	{
		//printf("Can't open package database.");
		sqlite3_close(db);
		return 255;
	}
	rc = sqlite3_prepare_v2(db, sql_str, -1, &res, 0);
	if(rc != SQLITE_OK)
	{
		//printf("DB Error: %s\n", sqlite3_errmsg(db));
		sqlite3_free(zErrMsg);
		sqlite3_close(db);
		return 0;
	}
	while(1)
	{
		result=sqlite3_step(res);
		if(result==SQLITE_ROW)
		{
		} else {
			break;
		}
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
	sql_str[0]='\0';
	return 1;
}

int transfer_domain(char user[20], char userkey[16], char newuser[20], char newuserkey[16], char tld[5], char domain[50])
{
	return 1;
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
	char *olduser;
	char *olduserkey;
	int rc=0;
	//cgiDebug(2, 1);
	cgi = cgiInit();

	if(cmd=cgiGetValue(cgi, "cmd"))
	{
		if(!strcmp(cmd, "check"))
		{
			user=cgiGetValue(cgi, "user");
			userkey=cgiGetValue(cgi, "userkey");
			tld=cgiGetValue(cgi, "tld");
			domain=cgiGetValue(cgi, "domain");
			if(verify(user, userkey))
			{
				rc=domain_exists(tld, domain);
				notify(rc);
			} else {
				notify(255);
			}
			return 0;
		}
		else if(!strcmp(cmd, "register"))
		{
			user=cgiGetValue(cgi, "user");
			userkey=cgiGetValue(cgi, "userkey");
			tld=cgiGetValue(cgi, "tld");
			domain=cgiGetValue(cgi, "domain");
			name=cgiGetValue(cgi, "name");
			email=cgiGetValue(cgi, "email");
			ns1=cgiGetValue(cgi, "ns1");
			ns2=cgiGetValue(cgi, "ns2");
			/* verify user and key */
			if(verify(user, userkey))
			{
				rc=register_domain(tld, domain, name, email, ns1, ns2);
				notify(rc);
			} else {
				notify(255);
			}
			return 0;
		}
		else if(!strcmp(cmd, "update"))
		{
			user=cgiGetValue(cgi, "user");
			userkey=cgiGetValue(cgi, "userkey");
			tld=cgiGetValue(cgi, "tld");
			domain=cgiGetValue(cgi, "domain");
			name=cgiGetValue(cgi, "name");
			email=cgiGetValue(cgi, "email");
			ns1=cgiGetValue(cgi, "ns1");
			ns2=cgiGetValue(cgi, "ns2");
			if(verify(user, userkey))
			{
				rc=update_domain(tld, domain, name, email, ns1, ns2);
				notify(rc);
			} else {
				notify(255);
			}
			return 0;
		}
		/* TODO
		else if(!strcmp(cmd, "transfer"))
		{
			user=cgiGetValue(cgi, "user");
			userkey=cgiGetValue(cgi, "userkey");
			olduser=cgiGetValue(cgi, "olduser");
			olduserkey=cgiGetValue(cgi, "olduserkey");
			tld=cgiGetValue(cgi, "tld");
			domain=cgiGetValue(cgi, "domain");
			if(verify(user, userkey))
			{
				rc=transfer_domain(user, userkey, olduser, olduserkey, tld, domain);
				notify(rc);
			} else {
				notify(255);
			}
			return 0;
		}
		*/
		/*
		else if(!strcmp(cmd, "delete"))
		{
			user=cgiGetValue(cgi, "user");
			userkey=cgiGetValue(cgi, "userkey");
			tld=cgiGetValue(cgi, "tld");
			domain=cgiGetValue(cgi, "domain");
			name=cgiGetValue(cgi, "name");
			if(verify(user, userkey))
			{
				rc=delete_domain(tld, domain, name, email);
				notify(rc);
			} else {
				notify(255);
			}
			return 0;
		}
		*/
		/*
		else if(!strcmp(cmd, "assist"))
		{
			user=cgiGetValue(cgi, "user");
			userkey=cgiGetValue(cgi, "userkey");
			tld=cgiGetValue(cgi, "tld");
			if(verify(user, userkey))
			{
				rc=get_support(tld);
				notify(rc);
			} else {
				notify(255);
			}
		}
		*/
	} else {
		printf("Content-type: text/html\n\n");
		printf("Unrecognised request.\n\n");
		return 0;
	}
	return 0;
}
