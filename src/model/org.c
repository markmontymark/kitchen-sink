#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../obj.h"
#include "org.h"

static char * ID   = "id";
static char * NAME = "name";

void  org_init(org_t * o)
{
	o->data->init( o->data );
}

void  org_save(org_t * o)
{
	o->data->save( o->data );
}


org_t * org_new()
{
   org_t * o = malloc(org_s);
   o->data = obj_new_simple();
   return o;
}

int  * org_get_id( org_t * o )
{
	return (int*) ( o->data->get(o->data, ID));
}

void   org_set_id( org_t * o, int * id )
{
	return o->data->set(o->data, ID, id);
}

char * org_get_name( org_t * o )
{
	return o->data->get(o->data, NAME);
}

void   org_set_name( org_t * o, char * name )
{
	return o->data->set(o->data, NAME, name);
}

void org_free(org_t * o)
{
	if( !o )
		return;	
	o->data->free(o->data);
   free(o);
}

