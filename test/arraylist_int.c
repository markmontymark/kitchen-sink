#include <stdio.h>
#include <string.h>
#include "../src/arraylist_int.h"

int main( int argc, char ** argv )
{

	int a = 1;
	int b = 10;
	int c = 100;
	int d = 2000;
	int e = 20;
	int f = 2;

	int i = 0;
	int n = 1;

	arraylist_int_t * list = arraylist_int_new();
	for(i = 0; i < 5; i++ )
	{
		n *= 10;
		arraylist_int_add(list,n);
	}
	
	arraylist_int_add(list,b);
	arraylist_int_add(list,c);
	arraylist_int_add(list,d);
	arraylist_int_add(list,e);
	arraylist_int_add(list,f);
	
	int sz = arraylist_int_size( list );
	printf("list size: %d\n", 	sz );
	for(int i = 0; i < sz; i++ )
	{
		printf("list[%d]: %d\n", i, arraylist_int_get( list, i ) );	
	}

	printf("list indexOf %d, expected %d, got %d, are equal? %s\n", 
		6, 
		100,
		arraylist_int_get( list, 6 ),
		100 == arraylist_int_get( list, 6 ) ? "Yes" : "No"
	);	
	
	arraylist_int_free( list );
	return 0;
}
