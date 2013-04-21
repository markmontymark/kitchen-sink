#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cfg.h"

cfg_t * cfg_new(cfg_impl_t * impl)
{
   cfg_t * c = malloc(cfg_s);
	//c->data = hashtable_new(); // TODO or null?
   c->initter = impl->initter;
   c->getter = impl->getter;
   c->setter = impl->setter;
   c->saver  = impl->saver;
   c->freer = impl->freer;
   c->dumper = impl->dumper;
	if(c->initter)
		c->initter(c);
   return c;
}

cfg_impl_t * cfg_impl_new(
   void   (*initter)(cfg_t *),
   void * (*getter) (cfg_t *,char *),
   void   (*setter) (cfg_t *,char *,void *),
   void   (*saver)  (cfg_t *),
   void   (*freer)  (cfg_t *),
   void   (*dumper) (cfg_t *,FILE *fp)
) 
{
   cfg_impl_t * i = malloc(cfg_impl_s);
	i->initter  = initter;
	i->getter  = getter;
	i->setter  = setter;
	i->saver  = saver;
	i->freer  = freer;
	i->dumper  = dumper;
	return i;
}


void * cfg_get( cfg_t * c, char * key)
{
	return c->getter(c->data,key);
}
char * cfg_get_str(cfg_t * c, char * key)
{
	return (char *) c->getter(c->data,key);
}

int    cfg_get_int(cfg_t * c, char * key)
{
	return (int) c->getter(c->data,key);
}


void cfg_set( cfg_t * c, char * key, void * val)
{
	c->setter(c->data,key,val);
}

void cfg_free(cfg_t * c)
{
	if( !c )
		return;	
	free(c->data);
   free(c->initter);
   free(c->getter);
   free(c->setter);
   free(c->saver);
   free(c->freer);
   free(c->dumper);
}

void cfg_dump(cfg_t * c,FILE * fp)
{
	c->dumper(c,fp); // TODO should be c->data
}



