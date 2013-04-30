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
	void   (*save)(objn_t *);
	void   (*free)(objn_t *);
	void   (*dump)(objn_t *,FILE *fp);
};
#define objn_s sizeof(objn_t)

typedef struct objn_impl objn_impl_t;
struct objn_impl {
	void   (*init)(objn_t *);
	void * (*get) (objn_t *,char *);
	void   (*set) (objn_t *,char *,void *);
	void   (*save)(objn_t *);
	void   (*free)(objn_t *);
	void   (*dump)(objn_t *,FILE *fp);
};
#define objn_impl_s sizeof(objn_impl_t)

/**
* Create a new config object to hold config data
* @param format Format of config file
* @returns objn_t A malloc'd objn_t * object
*/
//objn_t * objn_new(objn_impl_t * impl);
objn_t * objn_hashtable_new();
void objn_destroy();

/**
* Create a objn_impl_t object to define an implementation for a objn_t to get/set/free/dump config data
* @param format Format of config file
* @returns objn_t A malloc'd objn_t * object
*/
objn_impl_t * objn_impl_new(
	void   (*init)(objn_t *),
	void * (*get) (objn_t *,char *),
	void   (*set) (objn_t *,char *,void *),
	void   (*save)(objn_t *),
	void   (*free)(objn_t *),
	void   (*dump)(objn_t *,FILE *fp)
);

#endif
