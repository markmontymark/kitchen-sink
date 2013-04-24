#include <stdio.h>
#include "../../src/model/user.h"

int main( int argc, char ** argv)
{
	user_t * u = user_new();

	printf("created user %p\n",u);

	user_set_name(u,"ken");
	printf("set user %s\n",user_get_name(u));

	user_free(u);
	return 0;
}
