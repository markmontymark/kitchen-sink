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

	char * ix    = "This is a line with text";
	char * ix_match = "This";
	char * ix_match2 = "line";
	int match_1_retval = str_indexof(ix,ix_match) ;
	int match_2_retval = str_indexof(ix,ix_match2);

	printf("Match one retval, %s found in %s at position %d\n",ix_match, ix,match_1_retval);
	printf("Match two retval, %s found in %s at position %d\n",ix_match2,ix,match_2_retval);
}
