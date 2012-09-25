#ifndef __INI_H_
#define __INI_H_


#include "vendor/hashtable.h"

struct _ini_t
{
	char * path;
	hash_table_t * cfg;	
};
typedef struct _ini_t ini_t;

enum ini_modes 
{
	INI_RELOADABLE,
	INI_READONLY
};


ini_t * ini_new();
ini_t * ini_new_from_path(char * path);
int  ini_has(ini_t * ini, char * name);
int ini_add(ini_t * ini, char * key,char * val);
char * ini_get(ini_t * ini, char * name);
void ini_dump( ini_t * ini, FILE * fp);

#endif
