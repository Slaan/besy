#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX   16
#define TRUE  1
#define FALSE 0
// mutex init
pthread_mutex_t rb_mutex = PTHREAD_MUTEX_INITIALIZER;
// condition variables
pthread_cond_t is_not_full  = PTHREAD_COND_INITIALIZER; 
pthread_cond_t is_not_empty = PTHREAD_COND_INITIALIZER;

int thread_id[4] = {0, 1, 2, 3};

typedef struct {
  int  buffer[MAX];
  int* p_in;
  int* p_out;
  int  count;
} rb;
rb x = {{0}, NULL, NULL, 0};
rb *p_rb = &x;

#define p_start (int *) (p_rb -> buffer)
#define p_end (int *) ((p_rb -> buffer) + MAX-1)

void* control(void* pid);
void* consumer(void* pid);
void* producer(void* pid);
void* Procuder(void* pid);

void* write_c(void* pid) {
  int i = 0;
  int z_var = 0;
  printf("Schreiber: Starte das Schreiben (PID: %d)\n", *(int*) pid);
  while(TRUE) {
    i++;
    z_var++;
    if(z_var > 9) {
       z_var = 0;
    }
    pthread_mutex_lock(&rb_mutex);
    while(p_rb->p_in == p_rb->p_out && p_rb->count == MAX) {
      printf("Schreiber: Buffer ist voll. Bin ratzen.\n");
      pthread_cond_wait(&is_not_full, &rb_mutex);
      printf("Schreiber: Bin aufgewacht. (Count: %d, PID: %d)\n", p_rb->count, 
                                                                  *(int*) pid);
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

int main(int argc, char** argv) {
  int i;
  pthread_t threads[4];
  printf("Main: Starte Programm\n");
  p_rb->p_in  = p_start;
  p_rb->p_out = p_start;
  p_rb->count = 0;
  printf("Main: Counter Wert %d\n", p_rb->count);
  pthread_create(&threads[0], NULL, (void*) read_rb , (void *) &thread_id[0]);
  pthread_create(&threads[1], NULL, (void*) write_c , (void *) &thread_id[1]);
  // join all threads
  for(i = 0; i < 2; i++) 
    pthread_join(threads[i], NULL);
  printf("Main: Alle threads sind tot.\n");
  return 0;
}

