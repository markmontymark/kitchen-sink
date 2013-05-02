// original source http://cs.gmu.edu/~white/CS571/Examples/Pthread/pc_five.c
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h> 
#include <errno.h>
#define SIZE 5

pthread_mutex_t region_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t space_available = PTHREAD_COND_INITIALIZER;
pthread_cond_t data_available = PTHREAD_COND_INITIALIZER;

int b[SIZE];  
int size = 0;  /* number of full elements */
int front,rear=0;  /* queue */
 
main()  
{
  pthread_t producer_thread; 
  pthread_t consumer_thread; 
  void *producer();
  void *consumer();
 

    pthread_create(&consumer_thread,NULL,consumer,NULL);
    pthread_create(&producer_thread,NULL,producer,NULL);
    pthread_join(consumer_thread,NULL);

}

void add_buffer(int i){
  b[rear] = i;
  rear = (rear+1) % SIZE;
  size++;
}

int get_buffer(){
  int v;
  v = b[front];
  front= (front+1) % SIZE;
  size--;
  return v ;
}
 
void *producer()
{
	int i = 0;
	while (1) {
	  pthread_mutex_lock(&region_mutex);
	  if (size == SIZE) {
		  pthread_cond_wait(&space_available,&region_mutex);
	  }
		//printf("producer about to add %d\n",i);
	  add_buffer(i);
	  pthread_cond_signal(&data_available);
	  pthread_mutex_unlock(&region_mutex);
	  i = i + 1;
	}
	pthread_exit(NULL);
}
void *consumer()
{
	int i,v;
	for (i=0;i<20;i++) {
		pthread_mutex_lock(&region_mutex);
		if (size == 0) {
			 pthread_cond_wait(&data_available,&region_mutex); 
		}
		v = get_buffer();
		//printf("consumer got %d\n",v);
		printf("got %d\n",v);
		pthread_cond_signal(&space_available);
		pthread_mutex_unlock(&region_mutex);
	}
	pthread_exit(NULL);
}
 

