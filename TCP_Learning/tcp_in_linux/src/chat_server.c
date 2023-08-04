#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/io.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#define BUF_SIZE 1024
#define MAX_CLNT 256


void* handle_clnt(void* arg);
void send_msg(char* msg, int len);
void error_msg(char* msg);

int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int main(int argc, char *argv[])
{

  return EXIT_SUCCESS;
}






void* handle_clnt(void* arg) {
  int clnt_sock = *((int*)arg);
  int str_len = 0;
  char msg[BUF_SIZE];

  while ((str_len = read(clnt_sock, msg, sizeof(msg))) != 0) {
    send_msg(msg, str_len);
  }

  // some clint want to disconnected...
  pthread_mutex_lock(&mutx);
  for (int i = 0; i < clnt_cnt; i ++) {
    if (clnt_sock == clnt_socks[i]) {
      while (i ++ < clnt_cnt - 1) {
        clnt_socks[i] = clnt_socks[i + 1];
      }
      break;
    }
  }
  clnt_cnt --;
  pthread_mutex_unlock(&mutx);
  close(clnt_sock);
  return NULL;
}


void send_msg(char* msg, int len) {
  pthread_mutex_lock(&mutx);
  for (int i = 0; i < clnt_cnt; i ++) {

  }
}


void error_msg(char* msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
