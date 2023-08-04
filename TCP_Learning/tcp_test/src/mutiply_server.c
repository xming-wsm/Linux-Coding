#define _XOPEN_SOURCE
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MSG_SIZE 50

void error_msg(char* msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}

void sig_child_process_callback(int sig) {
  pid_t pid;
  int status;
  pid = waitpid(-1, &status, WNOHANG);
  if (WIFEXITED(status)) {
    printf("Child Process %d End\n", WEXITSTATUS(status));
  }
}

int main(int argc, char *argv[])
{
  pid_t pid;
  int serv_sock, clnt_sock;
  struct sigaction sig_act;
  struct sockaddr_in serv_adr, clnt_adr;
  socklen_t adr_sz;
  char msg_buf[MSG_SIZE];
  int str_len, state;

  char* ip_temp;
  char* ip_server;

  // if (argc != 2) {
  //   printf("Usage: %s <port>\n", argv[0]);
  //   exit(1);
  // }

  // signal processing function
  sig_act.sa_handler = sig_child_process_callback;
  sigemptyset(&sig_act.sa_mask);
  sig_act.sa_flags = 0;
  state = sigaction(SIGCHLD, &sig_act, 0);

  // create server socket
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  int option = true;
  setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, sizeof(option));

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(9110);

  if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
    error_msg("bind() error");
  }

  ip_server = inet_ntoa(serv_adr.sin_addr);
  printf("Server Open Succes, IP: %s\n", ip_server);


  if (listen(serv_sock, 5) == -1) {
    error_msg("listen() error");
  }

  while (1) {
    adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
    if (clnt_sock == -1) {
      continue;
    } else {
      fputs("New Client Connected...\n", stdout);
    }

    // Create Child Process
    pid = fork();
    if (pid == -1) {
      close(clnt_sock);
      continue;
    }

    if (pid == 0) {
      close(serv_sock);
      while ((str_len = read(clnt_sock, msg_buf, MSG_SIZE)) != 0) {
        write(clnt_sock, msg_buf, str_len);
      }
      
      close(clnt_sock);
      fputs("Client Disconnected...\n", stdout);
      return 0; 
    } else {
        close(clnt_sock);
    }
  }
  close(serv_sock);
  return EXIT_SUCCESS;
}
