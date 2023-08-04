#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define OP_SIZE 4
#define RES_SIZE 4

void error_message(char* msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}


int main(int argc, char *argv[])
{
  int clnt_sock;
  int str_len;
  struct sockaddr_in clnt_addr;
  struct sockaddr_in serv_addr;
  char msg_buf[BUF_SIZE];

  if (argc != 3) {
    printf("Usage: %s <IP> <Port>\n", argv[0]);
  }

  clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (clnt_sock == -1) {
    error_message("socket() error");
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (connect(clnt_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    error_message("connect() error");
  } else {
    fputs("Connect to Server...\n", stdout);
  } 

  while (1) {
    fputs("Input message(Q to quite): ", stdout);
    fgets(msg_buf, BUF_SIZE, stdin);

    if ( !strcmp(msg_buf, "q\n") || !strcmp(msg_buf, "Q\n")) {
      break;
    }

    write(clnt_sock, msg_buf, BUF_SIZE - 1);
    str_len = read(clnt_sock, msg_buf, BUF_SIZE - 1);
    msg_buf[str_len] = '\0';

    printf("Message from server: %s", msg_buf);
  }

  close(clnt_sock);
  return EXIT_SUCCESS;
}
