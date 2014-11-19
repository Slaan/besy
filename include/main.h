#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_BUFFER_SIZE   1

// mutex init
pthread_mutex_t rb_mutex = PTHREAD_MUTEX_INITIALIZER;

// condition variables
pthread_cond_t is_not_full  = PTHREAD_COND_INITIALIZER; 
pthread_cond_t is_not_empty = PTHREAD_COND_INITIALIZER;

int thread_id[4] = {0, 1, 2, 3}; 

typedef struct {
  int  buffer[MAX_BUFFER_SIZE];
  int* p_in;
  int* p_out;
  int  count;
} rb; 

rb x = {{0}, NULL, NULL, 0}; 
rb *p_rb = &x; 

#define p_start (int *) (p_rb -> buffer)
#define p_end (int *) ((p_rb -> buffer) + MAX_BUFFER_SIZE-1)

#endif // MAIN_H
