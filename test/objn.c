#include <stdio.h>
#include "../src/objn.h"
#include "../src/objn_hashtable.h"

int main( int argc, char ** argv)
{
	objn_t * c = objn_hashtable_new();

	printf("created obj %p\n",c);
	printf("created obj data %p\n",c);

	c->set(c,"key1","val1");
	printf("set %s to %s\n","key1","val1");
	//printf("key1 = %s\n",(char*)obj_get(c,"key1"));
	printf("key1 with getter = %s\n",(char*)c->get(c,"key1"));
	printf("key1 = %s\n",(char*)c->get(c,"key1"));

	c->set(c,"key1","val1 changed"); // TODO, hashtable.c keeps duplicate key values around, instead of overwritting an existing key
	printf("key1 = %s\n",(char*)c->get(c,"key1"));

	printf("obj dump\n----------\n");
	c->dump(c,stdout);
	printf("----------\n");

	c->set(c,"key2","val2"); // TODO, hashtable.c keeps duplicate key values around, instead of overwritting an existing key
	printf("key2 = %s\n",(char*)c->get(c,"key2"));

	printf("obj dump\n----------\n");
	c->dump(c,stdout);
	printf("----------\n");

	objn_t * o2 = objn_hashtable_new();
	o2->set(o2,"o2key","o2val");
	o2->set(c, "obj:o2",o2); //was objn_set_obj
	objn_t * o2lookedup = c->get(c, "obj:o2");
	printf("obj_set_obj looked up o2 (%p), got o2lookedup %p\n",o2,o2lookedup);
	printf("first dump o2\n");
	o2->dump(o2,stdout);
	printf("then dump o2lookedup\n");
	c->dump(c,stdout);
	
	//obj_free(o2);

	c->free(c);
	return 0;
}
