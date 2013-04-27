/**
* @file obj.h
* @brief Base object which all other _t types contain as a pdata (pointer-to-data)
* @author Mark Koopman
*/

#include "../../src/vendor/hashtable.h"
#include "../../src/obj.h"
#include "../../src/model/perm.h"

#ifndef __KITCHEN_SINK_MODEL_GROUP_H_
#define __KITCHEN_SINK_MODEL_GROUP_H_

typedef struct group group_t;
struct group {
	obj_t * data;
};
#define group_s sizeof(group_t)

/**
* Create a new group object to hold config data
* @param format Format of config file
* @returns group_t A malloc'd group_t * object
*/
group_t * group_new();

//TODO, make these static in group.c to create privary?
void   group_init(group_t *);

/**
* A group_t object has a int * id
* @param group_t The obj object
* @returns int *
*/
int  * group_get_id( group_t * );

/**
* A group_t object has a int * id
* @param group_t The obj object
* @returns void
*/
void   group_set_id( group_t * , int * );

/**
* A group_t object has a char * name
* @param group_t The obj object
* @returns char *
*/
char * group_get_name( group_t * );

/**
* A group_t object has a char * name
* @param group_t The obj object
* @returns void
*/
void   group_set_name( group_t * , char * );

/**
* A group_t object has a list of perm_t * s
* @param group_t The obj object
* @returns void
*/
void   group_add_perm( group_t * , perm_t * );

/**
* A group_t object might have a perm_t *
* @param group_t The obj object
* @returns void
*/
int    group_has_perm( group_t * , perm_t * );


/**
* Serialiize a group_t object to disk
* @param group_t The obj object
* @returns void
*/
void   group_save(group_t *);

/**
* Cleanup a group_t object
* @param group_t The obj object
* @returns void
*/
void group_free(group_t *);

/**
* Print the data of a group object to file pointer
* @param group_t The obj object
* @param fp The out stream to write to
* @returns void
*/
void group_dump(group_t *, FILE *);

#endif
