#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* thread_main(void* arg) {
  int cnt = *((int *)arg);
  char* msg = malloc(sizeof(char) * 50);
  strcpy(msg, "This is the return value of thread\n");

  for (int i = 0; i < cnt; i ++) {
    sleep(1);
    fputs("Running Thread\n", stdout);
  }
  return (void *)msg;
}

int main(int argc, char *argv[])
{
  pthread_t t_id;
  int thread_para = 5;
  void* thread_return;

  if (pthread_create(&t_id, NULL, thread_main, (void *)&thread_para) != 0) {
    fputs("pthread_create() error\n", stderr);
    exit(1);
  }
  
  if (pthread_join(t_id, &thread_return) != 0) {  
    fputs("pthread_join() error\n", stderr);
    exit(1);
  }

  printf("Thread return message: %s\n", (char *)thread_return);

  free(thread_return);
  return EXIT_SUCCESS;
}
