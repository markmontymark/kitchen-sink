#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../../src/model/group.h"
#include "../../src/model/perm.h"

int main( int argc, char ** argv)
{
	group_t * u = group_new();
	assert( u != NULL );
	printf("created group %p\n",u);

	group_set_name(u,"ken");
	printf("set group %s\n",group_get_name(u));
	assert( strcmp(group_get_name(u),"ken") == 0 );

	perm_t * p = perm_new();
	perm_set_id(p,"1");
	perm_set_name(p,"read perm");
	assert( strcmp(perm_get_name(p),"read perm") == 0 );
	printf("created perm %s\n",perm_get_name(p));

	group_add_perm( u, p );
	printf("added perm %s to group %s\n",perm_get_name(p),group_get_name(u));

	assert( group_has_perm( u, p ) == 1 );
	printf("group %s has perm %s\n",group_get_name(u),perm_get_name(p));

	perm_free(p);
	group_free(u);
	return 0;
}
