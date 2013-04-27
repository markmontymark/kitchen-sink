#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../obj.h"
#include "group.h"

static char * PERMS = "perms";

void  group_init(group_t * u)
{
	u->data->init( u->data );
}

void  group_save(group_t * u)
{
	u->data->save( u->data );
}


group_t * group_new()
{
   group_t * u = malloc(group_s);
   u->data = obj_new_simple();
   return u;
}

int  * group_get_id( group_t * u )
{
	return u->data->get(u->data, OBJ_ID);
}

void   group_set_id( group_t * u, int * id)
{
	return u->data->set(u->data, OBJ_ID, id);
}

char * group_get_name( group_t * u )
{
	return u->data->get(u->data, OBJ_NAME);
}

void   group_set_name( group_t * u, char * name )
{
	u->data->set(u->data, OBJ_NAME, name);
}

void   group_add_perm( group_t * u , perm_t * p )
{
	obj_t * perms = (obj_t *)u->data->get( u->data, PERMS );
	if(perms == NULL)
	{
		printf("group had no perms\n");
		obj_set_obj( u->data, PERMS, obj_new_simple() );
		perms = (obj_t *)u->data->get( u->data, PERMS);
		printf("group had no perms, now perms is %p\n",u->data->get( u->data, PERMS));
		printf("group had no perms, now perms is %p\n",perms);
	}
	obj_set_obj(perms, perm_get_id(p), p);
	printf("after obj_set_obj in group_add_perm\n");
}

/**
* A group_t object might have a perm_t *
* @param group_t The obj object
* @returns void
*/
int    group_has_perm( group_t * u, perm_t * p)
{
	obj_t * perms = (obj_t *)u->data->get(u->data, PERMS);
	printf("got perms? %p\n",perms);
	printf("looking for perm with id %s\n",perm_get_id(p) );
	perm_t * perm = (perm_t *)perms->get(perms, perm_get_id(p) );
	printf("was perm null? %p\n",perm );
	return (perm != NULL);
}


void group_free(group_t * u)
{
	if( !u )
		return;	
	u->data->free(u->data);
   free(u);
}

