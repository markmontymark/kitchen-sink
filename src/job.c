/**
* @file job.h
* @brief Base obj for delegating work (func ptrs) to threads
* @author Mark Koopman
*/

#include "../src/obj.h"
#include "../src/job.h"
#include "../src/job_bossworker.h"
#include "../src/job_peer.h"
#include "../src/job_pipeline.h"
#include "../src/job_producer_consumer.h"

static job_impl_t * bossworker_impl;
static job_impl_t * peer_impl;
static job_impl_t * pipeline_impl;
static job_impl_t * producer_consumer_impl;

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
)
{
}

job_t * job_new_bossworker( void * ( * boss_func )( job_args_t *), void * ( * worker_func )( job_args_t *) )
{
}

// peer is just a bossworker where the boss also does the workers tasks too
job_t * job_new_peer( void * ( * workerfunc )( job_args_t * ) )
{
}

// pipeline is good for when you have a stream (store in job_args_t) 
job_t * job_new_pipeline( void * ( * func )( job_args_t * ) ) 
{
}

// uses a buffer where prod adds to buffer, consumer pulls from buffer
job_t * job_new_producer_consumer( void * ( * producer_func )( job_args_t * ), void * ( * consumer_func )( job_args_t * ) )
{
}


#endif
