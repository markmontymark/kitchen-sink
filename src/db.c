#include "db.h"
#include "prompt.h"

void db_login( MYSQL * conn, const char * const host, const char * const database)
{
	char * un = malloc(100);
	char * pw = malloc(100);
	prompt_noecho("User: ",un);
	prompt_noecho("Password: ",pw);
	
	//printf("Connecting...\n");
   mysql_init(conn);
   if (!mysql_real_connect(
			conn, host, un, pw, database, 0, NULL, 0)
	) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
	free(un);
	free(pw);
}

void db_void_query(MYSQL * conn, char * sql)
{
   if (mysql_query(conn, sql)) 
	{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
}

MYSQL_RES * db_query(MYSQL * conn, char * sql)
{
	db_void_query(conn,sql);
   return  mysql_use_result(conn);
}
	
void db_logout(MYSQL * conn)
{
   mysql_close(conn);
}

