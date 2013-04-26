#include <stdio.h>
#include "../../src/model/org.h"

int main( int argc, char ** argv)
{
	org_t * a = org_new();

	printf("created org %p\n",a);

	int id = 1;
	int * pid = &id;
	org_set_id(a, pid);
	int * got_id = org_get_id(a);
	printf("set org id %d\n", *got_id );

	org_set_name(a,"Super Frobinator, Inc");
	printf("set org name %s\n",org_get_name(a));

	org_free(a);
	return 0;
}
