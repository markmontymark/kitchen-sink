
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../src/str.h"
#include "../src/obj.h"
#include "../src/vendor/hashtable.h"

obj_t * obj_new(
   void   (*init)(obj_t *),
   void * (*get) (obj_t *,char *),
   void   (*set) (obj_t *,char *,void *),
   void   (*save)  (obj_t *),
   void   (*free)  (obj_t *),
   void   (*dump) (obj_t *,FILE *fp)
)
{
   obj_t * o = malloc(obj_s);
	//o->data = hash_table_new(MODE_COPY); 
	o->data = hash_table_new(MODE_VALUEREF); 
   o->init = init;
   o->get = get;
   o->set = set;
   o->save = save;
   o->free = free;
   o->dump = dump;
	if(init)
		init(o);  // TODO o or o->data?
   return o;
}

obj_t * obj_new_simple()
{
	return obj_new(
		obj_init,
		obj_get,
		obj_set,
		obj_save,
		obj_free,
		obj_dump
	);
}

void   obj_init( obj_t * o )
{
}

void   obj_save( obj_t * o )
{
}

void * obj_get( obj_t * o, char * key)
{
	return hash_table_lookup(o->data,key,strlen(key)+1);
}
char * obj_get_str(obj_t * o, char * key)
{
	return hash_table_lookup(o->data, key, strlen(key)+1);
}

int *  obj_get_int(obj_t * c, char * key)
{
	return (int *) c->get(c->data,key);
}


void obj_set( obj_t * o, char * key, void * val)
{
	HT_ADD_STR(o->data, key, (char*)val);
}


void obj_set_obj( obj_t * o, char * key, void * val)
{
	HT_ADD_OBJ(o->data, key, val);
}


void obj_free(obj_t * c)
{
	if( !c )
		return;	
	hash_table_delete( c->data );
	free(c);
}


void obj_hash_table_dump_func(FILE * fp, void * key,void * val)
{
   if( val != NULL && str_indexof( (char *)key,"obj:") == 0 )
	{
      fprintf(fp,"%s = (obj_t)\n",(char *)key, (char *)val);
      hash_table_iterate_file( ((obj_t*)val)->data,fp, obj_hash_table_dump_func);
	}
   else
      fprintf(fp,"%s = %s\n",(char *)key, (char *)val);
}


void obj_dump(obj_t * o,FILE * fp)
{
   hash_table_iterate_file(o->data,fp,obj_hash_table_dump_func);
}


