#include <stdio.h>
#include "../../src/model/account.h"

int main( int argc, char ** argv)
{
	account_t * a = account_new();

	printf("created account %p\n",a);

	int id = 1;
	int * pid = &id;
	account_set_id(a, pid);
	int * got_id = account_get_id(a);
	printf("set account id %d\n", *got_id );

	account_set_name(a,"ken");
	printf("set account name %s\n",account_get_name(a));

	account_free(a);
	return 0;
}
