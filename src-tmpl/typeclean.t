#include <stdio.h>
#include <string.h>
#include "../src/%typeclean%.h"

int main( int argc, char ** argv )
{
	%typeclean%_t * ptr = %typeclean%_new();
	
	int sz = %typeclean%_size( ptr );
	printf("ptr size: %d\n", 	sz );
	for(int i = 0; i < sz; i++ )
		printf("ptr[%d]: %s\n", i, %typeclean%_get( ptr, i ) );	
	%typeclean%_free( ptr );
	return 0;
}
