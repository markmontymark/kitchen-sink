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

obj_t * group_get_perms( group_t * g )
{
	return g->data->get( g->data, PERMS );
}

void   group_add_perm( group_t * u , perm_t * p )
{
	obj_t * perms = group_get_perms(u);
	if(perms == NULL)
	{
		obj_set_obj( u->data, PERMS, obj_new_simple() );
		perms = (obj_t *)u->data->get( u->data, PERMS);
	}
	obj_set_obj(perms, perm_get_id(p), p);
	printf("after obj_set_obj in group_add_perm\n");
}

int    group_has_perm( group_t * u, perm_t * p)
{
	obj_t * perms = group_get_perms( u );
	perm_t * perm = (perm_t *)perms->get(perms, perm_get_id(p) );
	return (perm != NULL);
}


void group_free(group_t * u)
{
	if( !u )
		return;	
	obj_t * perms = group_get_perms( u );
	perms->free(perms);
	u->data->free(u->data);
   free(u);
}

