/**
* @file cfg.h
* @brief Config object to hold simple char * key => char * val pairs
* @author Mark Koopman
*/

#ifndef __KITCHEN_SINK_CFG_H_
#define __KITCHEN_SINK_CFG_H_

typedef struct cfg cfg_t;
struct cfg {
	void * data;
	void   (*initter)(cfg_t *);
	void * (*getter) (cfg_t *,char *);
	void   (*setter) (cfg_t *,char *,void *);
	void   (*saver)  (cfg_t *);
	void   (*freer)  (cfg_t *);
	void   (*dumper) (cfg_t *,FILE *fp);
};
#define cfg_s sizeof(cfg_t)

typedef struct cfg_impl cfg_impl_t;
struct cfg_impl {
	void   (*initter)(cfg_t *);
	void * (*getter) (cfg_t *,char *);
	void   (*setter) (cfg_t *,char *,void *);
	void   (*saver)  (cfg_t *);
	void   (*freer)  (cfg_t *);
	void   (*dumper) (cfg_t *,FILE *fp);
};
#define cfg_impl_s sizeof(cfg_impl_t)

/**
* Create a new config object to hold config data
* @param format Format of config file
* @returns cfg_t A malloc'd cfg_t * object
*/
cfg_t * cfg_new(cfg_impl_t * impl);

/**
* Create a cfg_impl_t object to define an implementation for a cfg_t to get/set/free/dump config data
* @param format Format of config file
* @returns cfg_t A malloc'd cfg_t * object
*/
cfg_impl_t * cfg_impl_new(
	void   (*initter)(cfg_t *),
	void * (*getter) (cfg_t *,char *),
	void   (*setter) (cfg_t *,char *,void *),
	void   (*saver)  (cfg_t *),
	void   (*freer)  (cfg_t *),
	void   (*dumper) (cfg_t *,FILE *fp)
);

/**
* This is where you parse some datasource and fill in the void * data structure with your config data
* @param c A cfg_t object
* @returns void
*/
void cfg_init(cfg_t * c);

/**
* Get a char * val by lookup with a char * key
* @param key The char * key to use for the lookup through a common dot notation syntax
* @returns NULL Returns NULL if key is not in lookup
* @returns char * val Otherwise returns the char * val found
*/
void * cfg_get(cfg_t * c, char * key);
char * cfg_get_str(cfg_t * c, char * key);
int    cfg_get_int(cfg_t * c, char * key);

/**
* Add a new char * key to the lookup
* @param key A char * for the lookup to use as a key. Duplicate key have their value overwritten
* @param val A char * for the lookup to return for the key.
* @returns void
*/
void cfg_set(cfg_t * c, char * key, void * val);

/**
* Cleanup a cfg_t object
* @param cfg_t The cfg object
* @returns void
*/
void cfg_free(cfg_t * c);

/**
* Print the data of a cfg object to file pointer
* @param cfg_t The cfg object
* @param fp The out stream to write to
* @returns void
*/
void cfg_dump(cfg_t * c,FILE * fp);

#endif
