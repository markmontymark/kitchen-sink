// original source http://cs.gmu.edu/~white/CS571/Examples/Pthread/pc_five.c

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h> 
#include <errno.h>

#include "../src/job.h"

#ifndef __KITCHEN_SINK_JOB_PRODUCER_CONSUMER_H_
#define __KITCHEN_SINK_JOB_PRODUCER_CONSUMER_H_

#define JOB_PRODUCER_CONSUMER_BUFFER_SIZE 10


void job_producer_consumer_init(  job_t * o );
void job_producer_consumer_start( job_t * o );
void add_buffer(int i);
int get_buffer();

job_t * job_process_consumer_new( 
	void * ( * producer )( job_args_t * ),
	void * ( * consumer )( job_args_t * )
);


#endif
 

