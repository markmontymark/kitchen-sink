#include <stdio.h>
#include <string.h>
#include "vendor/hashtable.h"

static hash_table_t * _cfg;

void cfg_init( char * key)
{
	_cfg = hash_table_new(MODE_COPY);
}

char * cfg( char * key)
{
	return (char *) HT_LOOKUP(_cfg,key);
}


void cfg_set( char * key, char * val)
{
	HT_ADD(_cfg,key,val);
}

