#include <stdio.h>
#include <string.h>
#include "../src/objn.h"
#include "../src/arraylist_objn.h"

int main( int argc, char ** argv )
{

	objn_t * a = objn_hashtable_new();
	objn_t * b = objn_hashtable_new();
	objn_t * c = objn_hashtable_new();

	arraylist_objn_t * list = arraylist_objn_new();
	arraylist_objn_add(list,a);
	arraylist_objn_add(list,b);
	arraylist_objn_add(list,c);
	
	int sz = arraylist_objn_size( list );
	printf("list size: %d\n", 	sz );
	for(int i = 0; i < sz; i++ )
	{
		printf("list %d: %p\n", i, arraylist_objn_get( list, i ) );	
	}

	printf("list indexOf %d, expected %p, got %p, are equal? %s\n", 
		2, 
		c,
		arraylist_objn_get( list, 2 ),
		objn_compare(c, arraylist_objn_get( list, 2 ) ) == 1 ? "Yes" : "No"
	);	
	
	arraylist_objn_free( list );
	return 0;
}
