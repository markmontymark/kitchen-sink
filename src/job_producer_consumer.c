// original source http://cs.gmu.edu/~white/CS571/Examples/Pthread/pc_five.c

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h> 
#include <errno.h>

#include "../src/job_producer_consumer.h"

#define SIZE 10

void job_producer_consumer_init( job_t * o )
{
	pthread_mutex_t region_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t space_available = PTHREAD_COND_INITIALIZER;
	pthread_cond_t data_available = PTHREAD_COND_INITIALIZER;

	int buffer[SIZE];  
	o->set(o,"buffer",buffer);
	int size = 0;  /* number of full elements */
	int front,rear=0;  /* queue */

	pthread_t producer_thread; 
	pthread_t consumer_thread; 
	pthread_create(&consumer_thread,NULL,consumer,NULL);
	pthread_create(&producer_thread,NULL,producer,NULL);

	o->set_obj(o,"producer",producer_thread);
	o->set_obj(o,"consumer",consumer_thread);
}

void job_producer_consumer_start( job_t * o )
{
	pthread_t * consumer_thread = o->get(o,"consumer");
	pthread_join(consumer_thread,NULL);
}

void add_buffer(int i){
  buffer[rear] = i;
  rear = (rear+1) % SIZE;
  size++;
}

int get_buffer(){
  int v;
  v = buffer[front];
  front = (front+1) % SIZE;
  size--;
  return v ;
}
 

