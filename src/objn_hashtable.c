#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendor/hashtable.h"

#include "str.h"
#include "objn.h"
#include "objn_hashtable.h"

/* simple impl */

void objn_hashtable_init(objn_t * c)
{
	c->data = hash_table_new(MODE_VALUEREF);
}

void objn_hashtable_free(objn_t * c)
{
	hash_table_delete(c->data);
	free(c);
}

void * objn_hashtable_get(objn_t * c,char * key)
{
	return hash_table_lookup(c->data,key,strlen(key)+1);
}

void objn_hashtable_set(objn_t * c, char * key, void * data)
{
	char * val = (char *)data;
	hash_table_add(c->data, key, strlen(key)+1, val, strlen(val)+1);
}

void objn_hashtable_save(objn_t * c)
{
}

void objn_hashtable_dump_func(FILE * fp, void * key,void * val)
{
   if( val != NULL && str_indexof( (char *)key,"obj:") == 0 )
   {
      fprintf(fp,"%s = (obj_t)\n",(char *)key, (char *)val);
      hash_table_iterate_file( ((objn_t*)val)->data,fp, objn_hashtable_dump_func);
   }
   else
      fprintf(fp,"%s = %s\n",(char *)key, (char *)val);
}


void objn_hashtable_dump(objn_t * o,FILE * fp)
{
   hash_table_iterate_file(o->data,fp,objn_hashtable_dump_func);
}


/*
void objn_hashtable_dump(objn_t * c,FILE * fp)
{
	if(c->data == NULL)
		return;
	hash_table_dump(c->data,fp);
}
*/

objn_impl_t * objn_hashtable_impl()
{
	return objn_impl_new(
		objn_hashtable_init,
		objn_hashtable_get,
		objn_hashtable_set,
		objn_hashtable_save,
		objn_hashtable_free,
		objn_hashtable_dump
	);
};

objn_t * objn_hashtable_new()
{
	return objn_new(objn_hashtable_impl());
}

