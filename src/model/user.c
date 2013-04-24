#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../obj.h"
#include "user.h"

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
   //void   (*initter)(obj_t *),
   //void * (*getter) (obj_t *,char *),
   //void   (*setter) (obj_t *,char *,void *),
   //void   (*saver)  (obj_t *),
   //void   (*freer)  (obj_t *),
   //void   (*dumper) (obj_t *,FILE *fp)
   user_t * u = malloc(user_s);
   u->data = obj_new_simple();
	//o->data = hashtable_new(); // TODO or null?
   return u;
}

char * user_get_name( user_t * u )
{
	return u->data->get(u->data, "name");
}

void   user_set_name( user_t * u, char * name )
{
	return u->data->set(u->data, "name", name);
}

void user_free(user_t * u)
{
	if( !u )
		return;	
	u->data->free(u->data);
   free(u);
	// TODO add 'u = NULL;' ?
}

