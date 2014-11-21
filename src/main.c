#include "main.h"
#include "consumer.h"
#include "producer1.h"
#include "producer2.h"
#include "controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

  // mutex init
  pthread_mutex_t rb_mutex       = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t prod1_mutex    = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t prod2_mutex    = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t consumer_mutex = PTHREAD_MUTEX_INITIALIZER;

  // condition variables
  pthread_cond_t is_not_full   = PTHREAD_COND_INITIALIZER; 
  pthread_cond_t is_not_empty  = PTHREAD_COND_INITIALIZER;
  pthread_cond_t cond_prod1    = PTHREAD_COND_INITIALIZER;
  pthread_cond_t cond_prod2    = PTHREAD_COND_INITIALIZER;
  pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;

  bool is_running_prod1 = false;
  bool is_running_prod2 = false;
  bool is_running_consumer = false;

  rb  x     = {{0}, NULL, NULL, 0};
  rb* p_rb  = &x;

  int thread_id[4] = {0, 1, 2, 3};
  
  pthread_t threads[4];

int main(int argc, char** argv) {
  int i;
  for(i = 0; i < 4; i++)
    thread_id[i] = i;
  printf("Main: Starte Programm\n");
  p_rb->p_in  = p_start;
  p_rb->p_out = p_start;
  p_rb->count = 0;
  printf("Main: Counter Wert %d\n", p_rb->count);
  pthread_create(&threads[0], NULL, (void*) consumer , (void *) &thread_id[0]);
  pthread_create(&threads[1], NULL, (void*) producer1 , (void *) &thread_id[1]);
  pthread_create(&threads[2], NULL, (void*) producer2 , (void *) &thread_id[2]);
  pthread_create(&threads[3], NULL, (void*) controller, (void *) &thread_id[3]);
 // join all threads
  for(i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
    printf("exit %d\n", i);
  }
  printf("Main: Alle threads sind tot.\n");
  return 0;
}
