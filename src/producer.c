#include <stdio.h>

#include "producer.h"
#include "main.h"


// Thread 1: Produces small letters and writes in ringbuffer
void* producer1(void* pid) {
	int z_var = 0x60;
  int PID = *(int*) pid;
		printf("Producer: Starte das Schreiben (PID: %d)\n", PID);
		while(true) {
		 	while(!is_running_prod1) {
        pthread_mutex_lock(&prod1_mutex);
				pthread_cond_wait(&cond_prod1, &prod1_mutex);
        pthread_mutex_unlock(&prod1_mutex);	
			}
			z_var++;
			if(z_var > 0x7A) {
				z_var = 0x60;
			}
			pthread_mutex_lock(&rb_mutex);
			while(p_rb->p_in == p_rb->p_out && p_rb->count == MAX_BUFFER_SIZE) {
				printf("Producer1: Buffer ist voll. Bin ratzen.\n");
				pthread_cond_wait(&is_not_full, &rb_mutex);
				printf("Producer1: Bin aufgewacht. (Count: %d, PID: %d)\n", 
                                                p_rb->count, PID);
			}
		*(p_rb->p_in) = (char) z_var;
		printf("Producer1, PID %d: Zeichen wurde in Ringbuffer geschrieben.\n", PID);
		(p_rb->p_in)++;
		if((p_rb->p_in) > p_end) {
			p_rb->p_in = p_start;
		}
		(p_rb->count)++;
		if(p_rb->count != 0) {
			printf("Producer: Buffer nicht mehr voll.\n");
			pthread_cond_signal(&is_not_empty);
		}
		pthread_mutex_unlock(&rb_mutex);
		sleep(3);
		}
	printf("Producer1 beendet\n");
  return (NULL);
	}

// Thread 1: Produces small letters and writes in ringbuffer
void* producer2(void* pid) {
	int z_var = 0x40;
  int PID = *(int*) pid;
		printf("Producer2: Starte das Schreiben (PID: %d)\n", PID);
		while(true) {
		 	while(!is_running_prod2) {
        pthread_mutex_lock(&prod2_mutex);
				pthread_cond_wait(&cond_prod2, &prod2_mutex);
        pthread_mutex_unlock(&prod2_mutex);	
			}
			z_var++;
			if(z_var > 0x5A) {
				z_var = 0x40;
			}
			pthread_mutex_lock(&rb_mutex);
			while(p_rb->p_in == p_rb->p_out && p_rb->count == MAX_BUFFER_SIZE) {
				printf("Producer2: Buffer ist voll. Bin ratzen.\n");
				pthread_cond_wait(&is_not_full, &rb_mutex);
				printf("Producer2: Bin aufgewacht. (Count: %d, PID: %d)\n", 
                                                p_rb->count, PID);
			}
		*(p_rb->p_in) = (char) z_var;
		printf("Producer2: Zeichen wurde in Ringbuffer geschrieben.\n");
		(p_rb->p_in)++;
		if((p_rb->p_in) > p_end) {
			p_rb->p_in = p_start;
		}
		(p_rb->count)++;
		if(p_rb->count != 0) {
			printf("Producer2: Buffer nicht mehr voll.\n");
			pthread_cond_signal(&is_not_empty);
		}
		pthread_mutex_unlock(&rb_mutex);
		sleep(3);
		}
  printf("Producer2 beendet\n");
	return (NULL);
	}


