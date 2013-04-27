#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../../src/model/user.h"

int main( int argc, char ** argv)
{
	user_t * u = user_new();
	assert( u != NULL );
	printf("created user %p\n",u);
	user_set_name(u,"ken");
	printf("set user %s\n",user_get_name(u));
	assert( strcmp(user_get_name(u),"ken") == 0 );
	user_free(u);
	return 0;
}