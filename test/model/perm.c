#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../../src/model/perm.h"

int main( int argc, char ** argv)
{
	perm_t * u = perm_new();
	assert( u != NULL );
	printf("created perm %p\n",u);
	perm_set_name(u,"ken");
	printf("set perm %s\n",perm_get_name(u));
	assert( strcmp(perm_get_name(u),"ken") == 0 );
	perm_free(u);
	return 0;
}
