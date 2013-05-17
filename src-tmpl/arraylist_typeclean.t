#include <stdio.h>
#include <string.h>
#include "../src/arraylist_%typeclean%.h"

int main( int argc, char ** argv )
{
	arraylist_%typeclean%_t * list = arraylist_%typeclean%_new();
	arraylist_%typeclean%_add(list,"wowee blah blah");
	arraylist_%typeclean%_add(list,"zowee");
	arraylist_%typeclean%_add(list,"on");
	arraylist_%typeclean%_add(list,"the longest entry in the list");
	arraylist_%typeclean%_add(list,"t");
	
	int sz = arraylist_%typeclean%_size( list );
	printf("list size: %d\n", 	sz );
	for(int i = 0; i < sz; i++ )
	{
		printf("list[%d]: %s\n", i, arraylist_%typeclean%_get( list, i ) );	
	}

	printf("list indexOf %d, expected %s, got %s, are equal? %s\n", 
		2, 
		"on",
		arraylist_%typeclean%_get( list, 2 ),
		strcmp( "on", arraylist_%typeclean%_get( list, 2 ) ) == 0 ? "Yes" : "No"
	);	
	
	arraylist_%typeclean%_free( list );
	return 0;
}
