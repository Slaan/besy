#include "stdio.h"
#include "producer.h"



// Thread 1: Produces small letters and writes in ringbuffer
void* producer1(void* pid) {
	int i = 0;
	int z_var = 0x60;
		printf("Schreiber: Starte das Schreiben (PID: %d)\n", *(int*) pid);
		while(1) {
			i++;
			z_var++;
			if(z_var > 0x7A) {
				z_var = 97;
			}
			pthread_mutex_lock(&rb_mutex);
			while(p_rb->p_in == p_rb->p_out && p_rb->count == MAX) {
				printf("Schreiber: Buffer ist voll. Bin ratzen.\n");
				pthread_cond_wait(&is_not_full, &rb_mutex);
				printf("Schreiber: Bin aufgewacht. (Count: %d, PID: %d)\n", p_rb->count, *(int*) pid);
			}
		*(p_rb->p_in) = getmychar(z_var);
		(p_rb->p_in)++;
		if((p_rb->p_in) > p_end) {
			p_rb->p_in = p_start;
		}
		(p_rb->count)++;
		if(p_rb->count != 0) {
			printf("Schreiber: Buffer nicht mehr voll.\n");
			pthread_cond_signal(&is_not_empty);
		}
		pthread_mutex_unlock(&rb_mutex);
		sleep(1);
		}
	return (NULL);
	}

// Thread 1: Produces small letters and writes in ringbuffer
void* producer1(void* pid) {
	int i = 0;
	int z_var = 0x40;
		printf("Schreiber: Starte das Schreiben (PID: %d)\n", *(int*) pid);
		while(1) {
			i++;
			z_var++
			if(z_var > 0x5A) {
				z_var = 97;
			}
			pthread_mutex_lock(&rb_mutex);
			while(p_rb->p_in == p_rb->p_out && p_rb->count == MAX) {
				printf("Schreiber: Buffer ist voll. Bin ratzen.\n");
				pthread_cond_wait(&is_not_full, &rb_mutex);
				printf("Schreiber: Bin aufgewacht. (Count: %d, PID: %d)\n", p_rb->count, *(int*) pid);
			}
		*(p_rb->p_in) = z_var;
		(p_rb->p_in)++;
		if((p_rb->p_in) > p_end) {
			p_rb->p_in = p_start;
		}
		(p_rb->count)++;
		if(p_rb->count != 0) {
			printf("Schreiber: Buffer nicht mehr voll.\n");
			pthread_cond_signal(&is_not_empty);
		}
		pthread_mutex_unlock(&rb_mutex);
		sleep(1);
		}
	return (NULL);
	}
