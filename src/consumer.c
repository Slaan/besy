#include "consumer.h"

void* read_rb(void* pid) {
  int i = 0;
  printf("Leser: Starte das Lesen (PID: %d)\n", *(int*) pid);
  while(TRUE) {
    i++;
    pthread_mutex_lock(&rb_mutex);
    while(p_rb->count == 0) {
      printf("Leser: Buffer ist leer\n");
      pthread_cond_wait(&is_not_empty, &rb_mutex);
      printf("Leser: Bin aufgewacht. (Count: %d, PID: %d)\n", p_rb->count,
                                                              *(int*) pid);
    }
    (p_rb->p_out)--;
    if((p_rb->p_out) > p_end) {
      p_rb->p_out = p_start;
    }
    if(p_rb->count <= MAX) {
      printf("Leser: Buffer nicht voll.\n");
      pthread_cond_signal(&is_not_full);
    }
    pthread_mutex_unlock(&rb_mutex);
    sleep(1);
  }
  return (NULL);
}

