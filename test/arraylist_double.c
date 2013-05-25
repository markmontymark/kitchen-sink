#include <stdio.h>
#include <string.h>
#include "../src/arraylist_double.h"

int main( double argc, char ** argv )
{
	double a = 1;
	double b = 10;
	double c = 100;
	double d = 2000;
	double e = 20;
	double f = 2;

	int i = 0;
	double n = 1;

	arraylist_double_t * list = arraylist_double_new();
	for(i = 0; i < 5; i++ )
	{
		n *= 10;
		arraylist_double_add(list,n);
	}
	
	arraylist_double_add(list,b);
	arraylist_double_add(list,c);
	arraylist_double_add(list,d);
	arraylist_double_add(list,e);
	arraylist_double_add(list,f);
	
	int sz = arraylist_double_size( list );
	printf("list size: %d\n", 	sz );
	for(int i = 0; i < sz; i++ )
		printf("list[%d]: %f\n", i, arraylist_double_get( list, i ) );	

	printf("list indexOf %d, expected %f, got %f, are equal? %s\n", 
		6, 
		(double)100,
		arraylist_double_get( list, 6 ),
		(double)100 == arraylist_double_get( list, 6 ) ? "Yes" : "No"
	);	

	arraylist_double_free( list );
	return 0;
}
