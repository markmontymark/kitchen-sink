#include <stdio.h>
#include "../src/obj.h"

int main( int argc, char ** argv)
{
	obj_t * c = obj_new_simple();

	printf("created obj %p\n",c);
	printf("created obj data %p\n",c);

	obj_set(c,"key1","val1");
	printf("set %s to %s\n","key1","val1");
	//printf("key1 = %s\n",(char*)obj_get(c,"key1"));
	printf("key1 with getter = %s\n",(char*)c->get(c,"key1"));
	printf("key1 = %s\n",obj_get_str(c,"key1"));

	obj_set(c,"key1","val1 changed"); // TODO, hashtable.c keeps duplicate key values around, instead of overwritting an existing key
	printf("key1 = %s\n",obj_get_str(c,"key1"));

	printf("obj dump\n----------\n");
	obj_dump(c,stdout);
	printf("----------\n");

	obj_set(c,"key2","val2"); // TODO, hashtable.c keeps duplicate key values around, instead of overwritting an existing key
	printf("key2 = %s\n",obj_get_str(c,"key2"));

	printf("obj dump\n----------\n");
	obj_dump(c,stdout);
	printf("----------\n");

	obj_free(c);
	return 0;
}
