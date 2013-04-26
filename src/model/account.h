/**
* @file obj.h
* @brief Base object which all other _t types contain as a pdata (pointer-to-data)
* @author Mark Koopman
*/

#include "../../src/vendor/hashtable.h"
#include "../../src/obj.h"

#ifndef __KITCHEN_SINK_MODEL_ACCOUNT_H_
#define __KITCHEN_SINK_MODEL_ACCOUNT_H_

typedef struct account account_t;
struct account {
	obj_t * data;
};
#define account_s sizeof(account_t)

/**
* Create a new account object to hold config data
* @param format Format of config file
* @returns account_t A malloc'd account_t * object
*/
account_t * account_new();

//TODO, make these static in account.c to create privary?
void   account_init(account_t *);

/**
* Serialiize a account_t object to disk
* @param account_t The obj object
* @returns void
*/
void   account_save(account_t *);

/**
* A account_t object has a int * id
* @param account_t The obj object
* @returns int *
*/
int  * account_get_id( account_t * );

/**
* A account_t object has a int * id
* @param account_t The obj object
* @returns void
*/
void   account_set_id( account_t * , int * );

/**
* A account_t object has a char * name
* @param account_t The obj object
* @returns char *
*/
char * account_get_name( account_t * );

/**
* A account_t object has a char * name
* @param account_t The obj object
* @returns void
*/
void   account_set_name( account_t * , char * );


/**
* Cleanup a account_t object
* @param account_t The obj object
* @returns void
*/
void account_free(account_t *);

/**
* Print the data of a account object to file pointer
* @param account_t The obj object
* @param fp The out stream to write to
* @returns void
*/
void account_dump(account_t * c,FILE * fp);

#endif
