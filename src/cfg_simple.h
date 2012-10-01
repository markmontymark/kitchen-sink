#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendor/hashtable.h"
#include "cfg.h"

/* simple impl */

cfg_t * cfg_simple_new();
void   cfg_simple_init(cfg_t * c);
void * cfg_simple_get(cfg_t * c,char * key);
void   cfg_simple_set(cfg_t * c,char * key,void * data);
void   cfg_simple_save(cfg_t * c);
void   cfg_simple_dump(cfg_t * c,FILE * fp);
void   cfg_simple_free(cfg_t * c);

cfg_impl_t * cfg_simple_impl();
