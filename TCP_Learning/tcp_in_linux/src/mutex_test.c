#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREAD 100

pthread_mutex_t mutex;
int32_t num = 0;

void* thread_inc(void* arg) {
  pthread_mutex_lock(&mutex);
  for (int i =0; i < 500000; i ++) {
    num ++;
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}


void* thread_des(void* arg) {
  pthread_mutex_lock(&mutex);
  for (int i =0; i < 500000; i ++) {
    num --;
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t thread_id[NUM_THREAD];

  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < NUM_THREAD; i ++) {
    if (i % 2) {

      pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
    } else {

      pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
    }
  }

  for (int i = 0; i < NUM_THREAD; i ++) {
    pthread_join(thread_id[i], NULL);
  }

  printf("Result: %d\n", num);
  pthread_mutex_destroy(&mutex);

  return EXIT_SUCCESS;
}
