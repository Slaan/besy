#include "main.h"
#include "consumer.h"


void* consumer(void* pid) {
  printf("Consumer: Starte die Ausgabe (PID: %d)\n", *(int*) pid);
  while(true) {
    // check block through controller
    pthread_mutex_lock(&consumer_mutex);
    while(!is_running_consumer) {
      pthread_cond_wait(&cond_consumer, &consumer_mutex);
    }
    pthread_mutex_unlock(&consumer_mutex);
    // check buffer not empty
    pthread_mutex_lock(&rb_mutex);
    while(p_rb->count == 0) {
      printf("Consumer: Buffer ist leer\n");
      pthread_cond_wait(&is_not_empty, &rb_mutex);
      printf("Consumer: Bin aufgewacht. (Count: %d, PID: %d)\n", p_rb->count,
                                                                 *(int*) pid);
    }
    printf("Output: %c\n",*(p_rb->p_out));
    (p_rb->count)--;
    (p_rb->p_out)++;
    if((p_rb->p_out) > p_end) {
      p_rb->p_out = p_start;
    }
    if(p_rb->count <= MAX_BUFFER_SIZE) {
      printf("Consumer: Buffer nicht voll.\n");
      pthread_cond_signal(&is_not_full);
    }
    pthread_mutex_unlock(&rb_mutex);
    sleep(2);
  }
  printf("Consumer beendet\n");
  return (NULL);
}

