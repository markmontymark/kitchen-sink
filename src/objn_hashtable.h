#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendor/hashtable.h"

#ifndef __KITCHEN_SINK_OBJN_HASHTABLE_H_
#define __KITCHEN_SINK_OBJN_HASHTABLE_H_


/* simple impl */

void   objn_hashtable_init(objn_t * c);
void * objn_hashtable_get (objn_t * c,char * key);
void   objn_hashtable_set (objn_t * c,char * key,void * data);
void   objn_hashtable_save(objn_t * c);
void   objn_hashtable_dump(objn_t * c,FILE * fp);
void   objn_hashtable_dump_func(FILE * fp, void * key,void * val);
void   objn_hashtable_free(objn_t * c);

objn_impl_t * objn_hashtable_impl();
void objn_hashtable_destroy();


#endif
