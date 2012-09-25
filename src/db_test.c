#include <string.h>
#include "db.h"

int main(int argc, char ** argv) 
{
   MYSQL * conn;
   MYSQL_RES * res;
   MYSQL_ROW row;

   const char * const host = strdup(argv[1]);
	char db[] = "mysql";
	char sql[] = "show tables";
	db_login(conn,host,db);
	res = db_query(conn,sql);

   /* output table name */
   printf("MySQL Tables in mysql database:\n");
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s \n", row[0]);
   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
	return 0;
}
