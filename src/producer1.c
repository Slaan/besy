#include <stdio.h>

#include "producer1.h"
#include "main.h"


// Thread 1: Produces small letters and writes in ringbuffer
void* producer1(void* pid) {
	int z_var = 0x60;
  int PID = *(int*) pid;
		printf("Producer 1 (%d): starte prod 1\n", PID);
		while(true) {
      pthread_mutex_lock(&prod1_mutex);
		 	while(!is_running_prod1) {
				pthread_cond_wait(&cond_prod1, &prod1_mutex);
        pthread_mutex_unlock(&prod1_mutex);
        pthread_testcancel();
        pthread_mutex_lock(&prod1_mutex);
			}
      pthread_mutex_unlock(&prod1_mutex);	
			z_var++;
			if(z_var > 0x7A) {
				z_var = 0x60;
			}
			pthread_mutex_lock(&rb_mutex);
			while(p_rb->p_in == p_rb->p_out && p_rb->count == MAX_BUFFER_SIZE) {
				printf("Producer 1 (%d): Buffer ist voll.\n", PID);
        //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
        //printf("pre_condvar\n");
				pthread_cond_wait(&is_not_full, &rb_mutex);
        pthread_mutex_unlock(&rb_mutex);
        //printf("post_condvar\n");
        //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
        //printf("pre_testcancel\n");
        if(kill) {
          pthread_exit(NULL);
        }
        //pthread_testcancel();
        pthread_mutex_lock(&rb_mutex);
				//printf("Producer 1 (%d): Bin aufgewacht. (Count: %d)\n", PID, p_rb->count);
			}
	  	*(p_rb->p_in) = (char) z_var;
	  	printf("Producer 1 (%d): Zeichen wurde in Ringbuffer geschrieben.\n", PID);
	  	(p_rb->p_in)++;
  		if((p_rb->p_in) > p_end) {
			  p_rb->p_in = p_start;
		  }
		  (p_rb->count)++;
		  if(p_rb->count != 0) {
		  	printf("Producer 1 (%d): Buffer nicht leer.\n", PID);
		  	pthread_cond_signal(&is_not_empty);
		  }
		  pthread_mutex_unlock(&rb_mutex);
		  sleep(3);
		}
	printf("Producer1 beendet\n");
  return (NULL);
}
