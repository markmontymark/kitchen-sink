#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../obj.h"
#include "user.h"


void  user_init(user_t * u)
{
	u->data->init( u->data );
}

void  user_save(user_t * u)
{
	u->data->save( u->data );
}


user_t * user_new()
{
   user_t * u = malloc(user_s);
   u->data = obj_new_simple();
   return u;
}
void user_new_for_addr(user_t * u)
{
	u->data = obj_new_simple();
}

int  * user_get_id( user_t * u )
{
	return u->data->get(u->data, OBJ_ID);
}

void   user_set_id( user_t * u, int * id)
{
	return u->data->set(u->data, OBJ_ID, id);
}

char * user_get_name( user_t * u )
{
	return u->data->get(u->data, OBJ_NAME);
}

void   user_set_name( user_t * u, char * name )
{
	return u->data->set(u->data, OBJ_NAME, name);
}

void user_for_addr_free(user_t * u)
{
	if( !u )
		return;	
	u->data->free(u->data);
}

void user_free(user_t * u)
{
	if( !u )
		return;	
	u->data->free(u->data);
   free(u);
}

