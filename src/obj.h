/**
* @file obj.h
* @brief Base object which all other _t types contain as a pdata (pointer-to-data)
* @author Mark Koopman
*/

#ifndef __KITCHEN_SINK_OBJ_H_
#define __KITCHEN_SINK_OBJ_H_

#define OBJ_ID "ID"
#define OBJ_NAME "NAME"

typedef struct obj obj_t;
struct obj {
	void * data;
	void   (*init)(obj_t *);
	void * (*get) (obj_t *,char *);
	void   (*set) (obj_t *,char *,void *);
	void   (*save)  (obj_t *);
	void   (*free)  (obj_t *);
	void   (*dump) (obj_t *,FILE *fp);
};
#define obj_s sizeof(obj_t)

/**
* Create a new config object to hold config data
* @param format Format of config file
* @returns obj_t A malloc'd obj_t * object
*/
obj_t * obj_new(
	void   (*init)(obj_t *),
	void * (*get) (obj_t *,char *),
	void   (*set) (obj_t *,char *,void *),
	void   (*save)  (obj_t *),
	void   (*free)  (obj_t *),
	void   (*dump) (obj_t *,FILE *fp)
);
obj_t * obj_new_simple();

/**
* Get a char * val by lookup with a char * key
* @param key The char * key to use for the lookup through a common dot notation syntax
* @returns NULL Returns NULL if key is not in lookup
* @returns char * val Otherwise returns the char * val found
*/
void   obj_init(obj_t *);
void   obj_save(obj_t *);
void * obj_get(obj_t * c, char * key);
char * obj_get_str(obj_t * c, char * key);
int  * obj_get_int(obj_t * c, char * key);

/**
* Add a new char * key to the lookup with a char * value
* @param key A char * for the lookup to use as a key. Duplicate key have their value overwritten
* @param val A char * for the lookup to return for the key.
* @returns void
*/
void obj_set(obj_t * c, char * key, void * val);

/**
* Add a new char * key to the lookup with an arbitrary void * value
* @param key A char * for the lookup to use as a key. Duplicate key have their value overwritten
* @param val A void * for the lookup to return for the key.
* @returns void
*/
void obj_set_obj( obj_t * o, char * key, void * val);


/**
* Cleanup a obj_t object
* @param obj_t The obj object
* @returns void
*/
void obj_free(obj_t * c);

/**
* Print the data of a obj object to file pointer
* @param obj_t The obj object
* @param fp The out stream to write to
* @returns void
*/
void obj_dump(obj_t * c,FILE * fp);
void obj_hash_table_dump_func(FILE * fp, void * key,void * val);


#endif
