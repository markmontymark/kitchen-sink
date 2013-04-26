#include <stdio.h>
#include "../src/script.h"

int main(int argc, char ** argv)
{
	script_t * t = script_new(argv[0],"Test script");
	script_dump_rcfile(t,stdout);

	printf("Looking up \"%s\", w/ default value \"%s\": returned: %s\n",
		"sc_dir","shouldn't be used", script_config(t, "sc_dir", "shouldn't be used"));
	printf("Looking up \"%s\", w/ default value \"%s\": returned: %s\n",
		"asdfasdf","should be used", script_config(t, "asdfasdf","should be used"));
	script_free(t);
}
