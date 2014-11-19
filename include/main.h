#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_BUFFER_SIZE   16
#define p_start (int *) (p_rb -> buffer)
#define p_end (int *) ((p_rb -> buffer) + MAX_BUFFER_SIZE-1)

// mutex init
extern pthread_mutex_t rb_mutex;
extern pthread_mutex_t prod1_mutex;
extern pthread_mutex_t prod2_mutex;
extern pthread_mutex_t consumer_mutex;

// condition variables
extern pthread_cond_t is_not_full;
extern pthread_cond_t is_not_empty;
extern pthread_cond_t cond_prod1;
extern pthread_cond_t cond_prod2;
extern pthread_cond_t cond_consumer;

// thread running bools
extern bool is_running_prod1;
extern bool is_running_prod2;
extern bool is_running_consumer;

// thread ids
extern int thread_id[4]; 

typedef struct {
  int  buffer[MAX_BUFFER_SIZE];
  int* p_in;
  int* p_out;
  int  count;
} rb; 

// ringbuffer instance and his pointer
extern rb  x; 
extern rb* p_rb; 

#endif // MAIN_H
