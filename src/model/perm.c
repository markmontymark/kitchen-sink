#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../obj.h"
#include "perm.h"

static char * PERM_ENABLED = "enabled";

void  perm_init(perm_t * u)
{
	u->data->init( u->data );
}

void  perm_save(perm_t * u)
{
	u->data->save( u->data );
}


perm_t * perm_new()
{
   perm_t * u = malloc(perm_s);
   u->data = obj_new_simple();
   return u;
}

char  * perm_get_id( perm_t * u )
{
	return u->data->get(u->data, OBJ_ID);
}

void   perm_set_id( perm_t * u, char * id)
{
	return u->data->set(u->data, OBJ_ID, id);
}

char * perm_get_name( perm_t * u )
{
	return u->data->get(u->data, OBJ_NAME);
}

void   perm_set_name( perm_t * u, char * name )
{
	return u->data->set(u->data, OBJ_NAME, name);
}

int  * perm_get_enabled( perm_t * u )
{
	return u->data->get(u->data, PERM_ENABLED);
}

void   perm_set_enabled( perm_t * u, int * id)
{
	u->data->set(u->data, PERM_ENABLED, id);
}


void perm_free(perm_t * u)
{
	if( !u )
		return;	
	u->data->free(u->data);
   free(u);
}

