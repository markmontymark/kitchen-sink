/**
* @file obj.h
* @brief Base object which all other _t types contain as a pdata (pointer-to-data)
* @author Mark Koopman
*/

#include "../../src/vendor/hashtable.h"
#include "../../src/obj.h"

#ifndef __KITCHEN_SINK_MODEL_USER_H_
#define __KITCHEN_SINK_MODEL_USER_H_

typedef struct user user_t;
struct user {
	obj_t * data;
};
#define user_s sizeof(user_t)

/**
* Create a new user object to hold config data
* @param format Format of config file
* @returns user_t A malloc'd user_t * object
*/
user_t * user_new();

//TODO, make these static in user.c to create privary?
void   user_init(user_t *);

/**
* A user_t object has a int * id
* @param user_t The obj object
* @returns int *
*/
int  * user_get_id( user_t * );

/**
* A user_t object has a int * id
* @param user_t The obj object
* @returns void
*/
void   user_set_id( user_t * , int * );

/**
* A user_t object has a char * name
* @param user_t The obj object
* @returns char *
*/
char * user_get_name( user_t * );

/**
* A user_t object has a char * name
* @param user_t The obj object
* @returns void
*/
void   user_set_name( user_t * , char * );

/**
* Serialiize a user_t object to disk
* @param user_t The obj object
* @returns void
*/
void   user_save(user_t *);

/**
* Cleanup a user_t object
* @param user_t The obj object
* @returns void
*/
void user_free(user_t *);

/**
* Print the data of a user object to file pointer
* @param user_t The obj object
* @param fp The out stream to write to
* @returns void
*/
void user_dump(user_t *, FILE *);

#endif
