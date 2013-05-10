#include <stdio.h>
#include "../src/arraylist_str.h"

int main( int argc, char ** argv )
{
	arraylist_str_t * list = arraylist_str_new();
	arraylist_str_add(list,"wowee blah blah");
	arraylist_str_add(list,"zowee");
	arraylist_str_add(list,"on");
	arraylist_str_add(list,"the longest entry in the list");
	arraylist_str_add(list,"t");
	
	int sz = arraylist_str_size( list );
	printf("list size: %d\n", 	sz );
	for(int i = 0; i < sz; i++ )
	{
		printf("list[%d]: %s\n", i, arraylist_str_get( list, i ) );	
	}

	printf("list indexOf %d, expected %s, got %s, are equal? %s\n", 
		2, 
		"on",
		arraylist_str_get( list, 2 ),
		strcmp( "on", arraylist_str_get( list, 2 ) ) == 0 ? "Yes" : "No"
	);	
	
	arraylist_str_free( list );
	return 0;
}
