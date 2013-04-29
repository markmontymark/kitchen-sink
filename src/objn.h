/**
* @file objn.h
* @brief Config object to hold simple char * key => char * val pairs
* @author Mark Koopman
*/

#ifndef __KITCHEN_SINK_OBJN_H_
#define __KITCHEN_SINK_OBJN_H_

typedef struct objn objn_t;
struct objn {
	void * data; // should be malloc'd, initialized in an implementation's init() (or lazy load in set/get?)
	void   (*init)(objn_t *);
	void * (*get) (objn_t *,char *);
	void   (*set) (objn_t *,char *,void *);
	void   (*save)  (objn_t *);
	void   (*free)  (objn_t *);
	void   (*dump) (objn_t *,FILE *fp);
};
#define objn_s sizeof(objn_t)

typedef struct objn_impl objn_impl_t;
struct objn_impl {
	void   (*init)(objn_t *);
	void * (*get) (objn_t *,char *);
	void   (*set) (objn_t *,char *,void *);
	void   (*save)  (objn_t *);
	void   (*free)  (objn_t *);
	void   (*dump) (objn_t *,FILE *fp);
};
#define objn_impl_s sizeof(objn_impl_t)

/**
* Create a new config object to hold config data
* @param format Format of config file
* @returns objn_t A malloc'd objn_t * object
*/
objn_t * objn_new(objn_impl_t * impl);

/**
* Create a objn_impl_t object to define an implementation for a objn_t to get/set/free/dump config data
* @param format Format of config file
* @returns objn_t A malloc'd objn_t * object
*/
objn_impl_t * objn_impl_new(
	void   (*init)(objn_t *),
	void * (*get) (objn_t *,char *),
	void   (*set) (objn_t *,char *,void *),
	void   (*save)  (objn_t *),
	void   (*free)  (objn_t *),
	void   (*dump) (objn_t *,FILE *fp)
);

/**
* Get a char * val by lookup with a char * key
* @param key The char * key to use for the lookup through a common dot notation syntax
* @returns NULL Returns NULL if key is not in lookup
* @returns char * val Otherwise returns the char * val found
*
void * objn_get(objn_t * c, char * key);
char * objn_get_str(objn_t * c, char * key);
int  * objn_get_int(objn_t * c, char * key);

**
* Add a new char * key to the lookup
* @param key A char * for the lookup to use as a key. Duplicate key have their value overwritten
* @param val A char * for the lookup to return for the key.
* @returns void
*
void objn_set(objn_t * c, char * key, void * val);
void objn_set_obj( objn_t * o, char * key, void * val);


**
* Cleanup a objn_t object
* @param objn_t The objn object
* @returns void
*
void objn_free(objn_t * c);

**
* Print the data of a objn object to file pointer
* @param objn_t The objn object
* @param fp The out stream to write to
* @returns void
*
void objn_dump(objn_t * c,FILE * fp);
*/

#endif
