#include <string.h>
#include "../src/db.h"

int main(int argc, char ** argv) 
{
   MYSQL conn;
   MYSQL_RES * res;
   MYSQL_ROW row;

	if( argc < 2 )
	{
		printf("Error, no hostname passed to db_test\n");
		printf("Usage: db_test <hostname>\n");
		exit(1);
	}

   const char * const host = strdup(argv[1]);
	char * db  = "test";
	char * stringy  = "stringy test string";

	char * step0_sql = "show tables";

	char * step1_sql = "\
		CREATE TABLE IF NOT EXISTS \
		dbtest(\
			id INT NOT NULL AUTO_INCREMENT,\
			stringy VARCHAR(100) DEFAULT 'def',\
			PRIMARY KEY(id)\
		)";

	char * step2_sql = "INSERT INTO dbtest (stringy) VALUES ('stringy test string')";
	char * step3_sql = "SELECT id,stringy FROM dbtest";
	char * step4_sql = "DELETE FROM dbtest";
	char * step5_sql = "DROP TABLE dbtest";

	// connect 
	db_login(&conn,host,db);

   printf("opened mysql connection\n");
   // step 0, basic query
	res = db_query(&conn, step0_sql);
   while ((row = mysql_fetch_row(res)) != NULL)
		printf("step0: %s\n", row[0]);
   mysql_free_result(res);

   // step 1, create simple table
	db_void_query(&conn, step1_sql);
   printf("step1: create simple table\n");

   // step 2, insert into simple table
	db_void_query(&conn, step2_sql);
   printf("step2: insert simple table\n");

   // step 3, select 
	res = db_query(&conn, step3_sql);
   while ((row = mysql_fetch_row(res)) != NULL)
		printf("step3: select from insert simple table, %s %s\n",row[0],row[1]);
   mysql_free_result(res);

   // step 4, delete test data
	db_void_query(&conn, step4_sql);
   printf("step4: delete simple data\n");

   // step 5, drop test table
	db_void_query(&conn, step5_sql);
   printf("step5: drop simple table\n");

   mysql_close(&conn);
   printf("close mysql connection\n");
	return 0;
}
