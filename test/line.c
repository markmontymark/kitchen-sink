#include <stdio.h>
#include <string.h>
#include "../src/line.h"

int main( int argc, char ** argv )
{
	line_t * ptr;
	int sz;

	char * lines[3] = {
		"goober",
		"",
		"Looks like a real line.\n"
	};
	for(int i=0; i < 3; i++)
	{
		ptr = line_new();
		line_set(ptr , lines[i]);	
		sz = line_size( ptr );
		printf("ptr size: %d\n", sz );
		printf("ptr data: %s\n", line_get(ptr) );
		printf("ends in newline: %s\n", line_has_newline( ptr ) ? "Yes" : "No"  );	
		printf("null terminated: %s\n", line_null_terminated( ptr ) ? "Yes" : "No" );	
		line_free( ptr );
		printf("line after free is null? %s\n", ptr == NULL ? "Yes" : "No" );	
	}

	return 0;
}
