#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "objn.h"
#include "obj.h"
#include "vendor/hashtable.h"

objn_t * objn_new(objn_impl_t * impl)
{
   objn_t * c = malloc(objn_s);
   c->init = impl->init;
   c->get = impl->get;
   c->set = impl->set;
   c->save  = impl->save;
   c->free = impl->free;
   c->dump = impl->dump;
	if(c->init)
		c->init(c);
   return c;
}

objn_impl_t * objn_impl_new(
   void   (*init)(objn_t *),
   void * (*get) (objn_t *,char *),
   void   (*set) (objn_t *,char *,void *),
   void   (*save)  (objn_t *),
   void   (*free)  (objn_t *),
   void   (*dump) (objn_t *,FILE *fp)
) 
{
   objn_impl_t * i = malloc(objn_impl_s);
	i->init  = init;
	i->get  = get;
	i->set  = set;
	i->save  = save;
	i->free  = free;
	i->dump  = dump;
	return i;
}

/*
void * objn_get( objn_t * c, char * key)
{
	return c->get(c,key);
}
char * objn_get_str(objn_t * c, char * key)
{
	return (char *) c->get(c,key);
}

int *   objn_get_int(objn_t * c, char * key)
{
	return (int *) c->get(c,key);
}

void objn_set( objn_t * c, char * key, void * val)
{
	c->set(c,key,val);
}
void objn_set_obj( objn_t * o, char * key, void * val)
{
   HT_ADD_OBJ(o->data, key, val);
}


void objn_free(objn_t * c)
{
	if( !c )
		return;	
	if(c->free)
		c->free(c);
}

void objn_dump(objn_t * c,FILE * fp)
{
	c->dump(c,fp); // TODO should be c->data
}
*/


