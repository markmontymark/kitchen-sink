/**
* @file obj.h
* @brief Base object which all other _t types contain as a pdata (pointer-to-data)
* @author Mark Koopman
*/

#include "../../src/vendor/hashtable.h"
#include "../../src/obj.h"

#ifndef __KITCHEN_SINK_MODEL_ORG_H_
#define __KITCHEN_SINK_MODEL_ORG_H_

typedef struct org org_t;
struct org {
	obj_t * data;
};
#define org_s sizeof(org_t)

/**
* Create a new org object to hold config data
* @param format Format of config file
* @returns org_t A malloc'd org_t * object
*/
org_t * org_new();

//TODO, make these static in org.c to create privary?
void   org_init(org_t *);

/**
* Serialiize a org_t object to disk
* @param org_t The obj object
* @returns void
*/
void   org_save(org_t *);

/**
* A org_t object has a int * id
* @param org_t The obj object
* @returns int *
*/
int  * org_get_id( org_t * );

/**
* A org_t object has a int * id
* @param org_t The obj object
* @returns void
*/
void   org_set_id( org_t * , int * );

/**
* A org_t object has a char * name
* @param org_t The obj object
* @returns char *
*/
char * org_get_name( org_t * );

/**
* A org_t object has a char * name
* @param org_t The obj object
* @returns void
*/
void   org_set_name( org_t * , char * );


/**
* Cleanup a org_t object
* @param org_t The obj object
* @returns void
*/
void org_free(org_t *);

/**
* Print the data of a org object to file pointer
* @param org_t The obj object
* @param fp The out stream to write to
* @returns void
*/
void org_dump(org_t * c,FILE * fp);

#endif
