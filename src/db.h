#ifndef __LIBMRK_DB_MYSQL_H_
#define __LIBMRK_DB_MYSQL_H_

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   

//static char * pw;
//static char * un;

//static void db_get_un_pw(); // called by db_login
void db_login( MYSQL * conn, const char * const host, const char * const database);
void db_void_query(MYSQL * conn, char * sql);
MYSQL_RES * db_query(MYSQL * conn, char * sql);
void db_logout(MYSQL * conn);

#endif
