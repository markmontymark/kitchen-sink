#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../obj.h"
#include "account.h"


void  account_init(account_t * o)
{
	o->data->init( o->data );
}

void  account_save(account_t * o)
{
	o->data->save( o->data );
}

account_t * account_new()
{
   account_t * o = malloc(account_s);
   o->data = obj_new_simple();
   return o;
}

int  * account_get_id( account_t * o )
{
	return (int*) ( o->data->get(o->data, OBJ_ID));
}

void   account_set_id( account_t * o, int * id )
{
	return o->data->set(o->data, OBJ_ID, id);
}

char * account_get_name( account_t * o )
{
	return o->data->get(o->data, OBJ_NAME);
}

void   account_set_name( account_t * o, char * name )
{
	return o->data->set(o->data, OBJ_NAME, name);
}

void account_free(account_t * o)
{
	if( !o )
		return;	
	o->data->free(o->data);
   free(o);
}

