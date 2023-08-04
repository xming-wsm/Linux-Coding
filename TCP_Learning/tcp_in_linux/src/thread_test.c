#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_main(void* arg) {
  int cnt = *((int*)arg);
  for (int i = 0; i < cnt; i ++) {
    sleep(1);
    fputs("running thread\n", stdout);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t t_id;
  int thread_para = 5;
  if (pthread_create(&t_id, NULL, thread_main, (void*)&thread_para) != 0) {
    fputs("pthread_create() error\n", stderr);
    exit(1);
  }

  sleep(10);
  fputs("End of main\n", stdout);

  return EXIT_SUCCESS;
}
