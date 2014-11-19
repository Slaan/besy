#include "main.h"
#include "consumer.h"
#include "main.h"


<<<<<<< HEAD
void* read_rb(void* pid) {
  int i = 0;
  printf("Leser: Starte das Lesen (PID: %d)\n", *(int*) pid);
  while(true) {
    i++;
=======
void* consumer(void* pid) {
  printf("Consumer: Starte die Ausgabe (PID: %d)\n", *(int*) pid);
  while(true) {
    // check block through controller
    pthread_mutex_lock(&consumer_mutex);
    while(!is_running_consumer) {
      pthread_cond_var(&cond_consumer, &consumer_mutex);
    }
    pthread_mutex_unlock(&consumer_mutex);
    // check buffer not empty
>>>>>>> 7aea932beba766faa347091696f91d710b50a23e
    pthread_mutex_lock(&rb_mutex);
    while(p_rb->count == 0) {
      printf("Consumer: Buffer ist leer\n");
      pthread_cond_wait(&is_not_empty, &rb_mutex);
      printf("Consumer: Bin aufgewacht. (Count: %d, PID: %d)\n", p_rb->count,
                                                                 *(int*) pid);
    }
    (p_rb->count)--;
    (p_rb->p_out)++;
    if((p_rb->p_out) > p_end) {
      p_rb->p_out = p_start;
    }
    if(p_rb->count <= MAX) {
      printf("Consumer: Buffer nicht voll.\n");
      pthread_cond_signal(&is_not_full);
    }
    pthread_mutex_unlock(&rb_mutex);
    sleep(1);
  }
  return (NULL);
}

