/**
* @file job.h
* @brief Base obj for delegating work (func ptrs) to threads
* @author Mark Koopman
*/

#include "../src/obj.h"

#ifndef __KITCHEN_SINK_JOB_H_
#define __KITCHEN_SINK_JOB_H_

typedef struct job job_t;
struct job {
	int numCPUs;
	int running;
	int left;
	obj_t * job_details;
};
#define job_s sizeof(job_t)

typedef struct job_impl job_impl_t;
struct job_impl {
	void   (*init  ) (job_t *);
	void * (*start ) (job_t *);
	void * (*stop  ) (job_t *);
	void   (*pause ) (job_t *);
	void   (*resume) (job_t *);
	void   (*free  ) (job_t *);
	void   (*dump  ) (job_t *,FILE *fp);
};
#define job_impl_s sizeof(job_impl_t)

typedef struct job_args job_args_t;
struct job_args {
	obj_t * data;
};
#define job_args_s sizeof(job_args_t)

/**
* Create a new job to hold implemetnation func ptrs for that specific type of thread
* @param init - func ptr to call on initializing a new job
* @returns job_t A malloc'd job_t * jobect
*/
job_impl_t * job_impl_new(
	void   (*init  ) (job_t *),
	void * (*start ) (job_t *),
	void * (*stop  ) (job_t *),
	void   (*pause ) (job_t *),
	void   (*resume) (job_t *),
	void   (*free  ) (job_t *),
	void   (*dump  ) (job_t *,FILE *fp)
);


job_t * job_new_bossworker( void * ( * boss_func )( job_args_t *), void * ( * worker_func )( job_args_t *) );
job_t * job_new_peer( void * ( * workerfunc )( job_args_t * ) ); // peer is just a bossworker where the boss also does the workers tasks too
job_t * job_new_pipeline( void * ( * func )( job_args_t * ) ); // pipeline is good for when you have a stream (store in job_args_t) 
job_t * job_new_producer_consumer( void * ( * producer_func )( job_args_t * ), void * ( * consumer_func )( job_args_t * ) ); // uses a buffer where prod adds to buffer, consumer pulls from buffer


#endif
