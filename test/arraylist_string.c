#include <stdio.h>
#include <string.h>
#include "../src/arraylist_string.h"

int main( int argc, char ** argv )
{
	arraylist_string_t * list = arraylist_string_new();
	arraylist_string_add(list,"wowee blah blah");
	arraylist_string_add(list,"zowee");
	arraylist_string_add(list,"on");
	arraylist_string_add(list,"the longest entry in the list");
	arraylist_string_add(list,"t");

	//printf("to_string output: %s\nend to_string output\n",arraylist_string_to_string(list));
	
	int sz = arraylist_string_size( list );
	printf("list size: %d\n", 	sz );
	for(int i = 0; i < sz; i++ )
	{
		printf("list[%d]: %s\n", i, arraylist_string_get( list, i ) );	
	}

	printf("list indexOf %d, expected %s, got %s, are equal? %s\n", 
		2, 
		"on",
		arraylist_string_get( list, 2 ),
		strcmp( "on", arraylist_string_get( list, 2 ) ) == 0 ? "Yes" : "No"
	);	
	
	arraylist_string_free( list );
	return 0;
}
