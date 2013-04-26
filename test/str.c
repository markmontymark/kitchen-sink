#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../src/str.h"

int main(int argc, char ** argv)
{	
	char * to_chomp    = "This is a line that ends in newline.\n";
	char * chomp_match = "This is a line that ends in newline.";
	char * retval= str_chomp(to_chomp);
	assert( strcmp( chomp_match, retval) == 0);
	free(retval);

	char * to_substr    = "This is a line with text";
	char * substr_match = "line";
	retval = str_substring(to_substr, 10, 14);
	assert( strcmp( substr_match, retval ) == 0 );
	free(retval);
	//int str_indexof(char * text,char delim);
}
