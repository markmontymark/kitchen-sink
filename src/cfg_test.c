#include <stdio.h>
#include "cfg.h"
#include "cfg_simple.h"

int main( int argc, char ** argv)
{
	cfg_t * c = cfg_simple_new();

	printf("created cfg %p\n",c);
	printf("created cfg data %p\n",c);

	cfg_set(c,"key1","val1");
	printf("key1 = %s\n",(char*)cfg_get(c,"key1"));
	printf("key1 = %s\n",cfg_get_str(c,"key1"));

	cfg_set(c,"key1","val1 changed"); // TODO, hashtable.c keeps duplicate key values around, instead of overwritting an existing key
	printf("key1 = %s\n",cfg_get_str(c,"key1"));

	printf("cfg dump\n----------\n");
	cfg_dump(c,stdout);
	printf("----------\n");

	cfg_set(c,"key2","val2"); // TODO, hashtable.c keeps duplicate key values around, instead of overwritting an existing key
	printf("key2 = %s\n",cfg_get_str(c,"key2"));

	printf("cfg dump\n----------\n");
	cfg_dump(c,stdout);
	printf("----------\n");

	cfg_free(c);
	return 0;
}
