#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendor/hashtable.h"

#include "cfg.h"
#include "cfg_simple.h"

/* simple impl */

void cfg_simple_init(cfg_t * c,void * notused)
{
	c->data = hash_table_new(MODE_COPY);
}
void cfg_simple_free(cfg_t * c)
{
	hash_table_delete(c->data);
	free(c);
}

void * cfg_simple_get(cfg_t * c,char * key)
{
	return hash_table_lookup(c->data,key,strlen(key)+1);
}

void cfg_simple_set(cfg_t * c,char * key,void * data)
{
	char * val = (char *)data;
	hash_table_add(c->data,key,strlen(key)+1, val,strlen(val)+1);
}

void cfg_simple_save(cfg_t * c)
{
}

void cfg_simple_dump(cfg_t * c,FILE * fp)
{
	if(c->data == NULL)
		return;
	hash_table_dump(c->data,fp);
}

cfg_impl_t * cfg_simple_impl()
{
	return cfg_impl_new(
		cfg_simple_init,
		cfg_simple_get,
		cfg_simple_set,
		cfg_simple_save,
		cfg_simple_free,
		cfg_simple_dump
	);
};


