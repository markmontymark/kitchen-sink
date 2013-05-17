#include <stdio.h>
#include <string.h>
#include "../src/arraylist_int_ptr.h"

int main( int argc, char ** argv )
{

	int a = 1;
	int *a_ptr = &a;
	int b = 10;
	int *b_ptr = &b;
	int c = 100;
	int *c_ptr = &c;
	int d = 2000;
	int *d_ptr = &d;
	int e = 20;
	int *e_ptr = &e;
	int f = 2;
	int *f_ptr = &f;

	arraylist_int_ptr_t * list = arraylist_int_ptr_new();
	arraylist_int_ptr_add(list,a_ptr);
	arraylist_int_ptr_add(list,b_ptr);
	arraylist_int_ptr_add(list,c_ptr);
	arraylist_int_ptr_add(list,d_ptr);
	arraylist_int_ptr_add(list,e_ptr);
	arraylist_int_ptr_add(list,f_ptr);
	
	int sz = arraylist_int_ptr_size( list );
	printf("list size: %d\n", 	sz );
	for(int i = 0; i < sz; i++ )
	{
		printf("list[%d]: %d\n", i, *(int*)arraylist_int_ptr_get( list, i ) );	
	}

	printf("list indexOf %d, expected %d, got %d, are equal? %s\n", 
		2, 
		100,
		*(int*)arraylist_int_ptr_get( list, 2 ),
		100 == *(int*) arraylist_int_ptr_get( list, 2 ) ? "Yes" : "No"
	);	
	
	arraylist_int_ptr_free( list );
	return 0;
}
