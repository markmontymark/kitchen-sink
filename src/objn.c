#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "objn.h"
#include "objn_hashtable.h"

static objn_impl_t * objn_impl_hashtable;

void objn_destroy()
{
	if(objn_impl_hashtable != NULL)
		free( objn_impl_hashtable );
	objn_impl_hashtable = NULL;
}

objn_t * objn_new(objn_impl_t * impl)
{
   objn_t * c = malloc(objn_s);
	if(c == NULL)
	{
		fprintf(stderr, "out of memory\n");
		exit(2);
	}
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

objn_t * objn_hashtable_new()
{
	return objn_new( objn_hashtable_impl() );
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
	if(i == NULL)
	{
		fprintf(stderr, "out of memory\n");
		exit(2);
	}
	i->init  = init;
	i->get  = get;
	i->set  = set;
	i->save  = save;
	i->free  = free;
	i->dump  = dump;
	return i;
}

