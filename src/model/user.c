#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../obj.h"
#include "user.h"

static char * NAME = "name";

void  user_init(user_t * u)
{
	printf("init user %p\n",u);
	u->data->init( u->data );
}

void  user_save(user_t * u)
{
	printf("save user %p\n",u);
	u->data->save( u->data );
}


user_t * user_new()
{
   user_t * u = malloc(user_s);
   u->data = obj_new_simple();
   return u;
}

char * user_get_name( user_t * u )
{
	return u->data->get(u->data, NAME);
}

void   user_set_name( user_t * u, char * name )
{
	return u->data->set(u->data, NAME, name);
}

void user_free(user_t * u)
{
	if( !u )
		return;	
	u->data->free(u->data);
   free(u);
}

