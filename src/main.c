#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <producer.h>

int main(int argc, char** argv) {
  int i;
  pthread_t threads[4];
  printf("Main: Starte Programm\n");
  p_rb->p_in  = p_start;
  p_rb->p_out = p_start;
  p_rb->count = 0;
  printf("Main: Counter Wert %d\n", p_rb->count);
  pthread_create(&threads[0], NULL, (void*) read_rb , (void *) &thread_id[0]);
  pthread_create(&threads[1], NULL, (void*) producer1 , (void *) &thread_id[1]);
  pthread_create(&threads[2], NULL, (void*) producer2 , (void *) &thread_id[2]);
 // join all threads
  for(i = 0; i < 2; i++) 
    pthread_join(threads[i], NULL);
  printf("Main: Alle threads sind tot.\n");
  return 0;
}

