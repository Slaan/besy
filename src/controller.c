#include <stdio.h>
#include <unistd.h>
#include <termios.h>

// to run local main
//#include "../include/controller.h"
//#include "../include/main.h"
#include "controller.h"
#include "main.h"

// copied from 
int mygetch() {
  struct termios oldt, newt;
  int ch;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return ch; 
}

inline void toggleProducer1() {
  pthread_mutex_lock(&prod1_mutex);
  is_running_prod1 = !is_running_prod1;
  pthread_mutex_unlock(&prod1_mutex);
}

inline void toggleProducer2() {
  pthread_mutex_lock(&prod2_mutex);
  is_running_prod2 = !is_running_prod2;
  pthread_mutex_unlock(&prod2_mutex);
}

inline void toggleConsumer() {
  pthread_mutex_lock(&consumer_mutex);
  is_running_consumer = !is_running_consumer;
  pthread_mutex_unlock(&consumer_mutex);
}

void printHelp() {
  printf("Programm beenden: q/Q\n");
  printf("Producer 1 blocken/starten: 1\n");
  printf("Producer 2 blocken/starten: 2\n");
  printf("Consumer blocken/starten: c\n");
  printf("Hilfe anzeigen: h\n");
}

void* controller(void* pid) {
  int  i    = 0;
  bool done = false;
  printf("Controller: Starte das Kontrollieren\n");
  while(!done) {
    i++;
    switch(mygetch()) {
      case 'Q': // nop
      case 'q': killOthers();
                done = true;
                break;
      case '1': toggleProducer1();
                break;
      case '2': toggleProducer2();
                break;
      case 'c': toggleConsumer();
                break;
      case 'h': printHelp();
                break;
      default:  // nop
                break;
    }
  }
  return (NULL);
}

/*
int main() {
  pthread_t thread;
  int id = 1;
  pthread_create(&thread, NULL, (void*) controller, (void*) &id);
  pthread_join(thread, NULL);
}
*/
