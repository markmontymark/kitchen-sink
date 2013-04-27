/**
* @file obj.h
* @brief Base object which all other _t types contain as a pdata (pointer-to-data)
* @author Mark Koopman
*/

#include "../../src/vendor/hashtable.h"
#include "../../src/obj.h"

#ifndef __KITCHEN_SINK_MODEL_USER_H_
#define __KITCHEN_SINK_MODEL_USER_H_

typedef struct perm perm_t;
struct perm {
	obj_t * data;
};
#define perm_s sizeof(perm_t)

/**
* Create a new perm object to hold config data
* @param format Format of config file
* @returns perm_t A malloc'd perm_t * object
*/
perm_t * perm_new();

//TODO, make these static in perm.c to create privary?
void   perm_init(perm_t *);

/**
* A perm_t object has a int * id
* @param perm_t The obj object
* @returns int *
*/
char  * perm_get_id( perm_t * );

/**
* A perm_t object has a int * id
* @param perm_t The obj object
* @returns void
*/
void   perm_set_id( perm_t * , char * );

/**
* A perm_t object has a char * name
* @param perm_t The obj object
* @returns char *
*/
char * perm_get_name( perm_t * );

/**
* A perm_t object has a char * name
* @param perm_t The obj object
* @returns void
*/
void   perm_set_name( perm_t * , char * );

/**
* Serialiize a perm_t object to disk
* @param perm_t The obj object
* @returns void
*/
void   perm_save(perm_t *);

/**
* Cleanup a perm_t object
* @param perm_t The obj object
* @returns void
*/
void perm_free(perm_t *);

/**
* Print the data of a perm object to file pointer
* @param perm_t The obj object
* @param fp The out stream to write to
* @returns void
*/
void perm_dump(perm_t *, FILE *);

#endif
