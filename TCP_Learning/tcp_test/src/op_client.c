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
  char message[BUF_SIZE];
  int result, op_number;
  struct sockaddr_in serv_adr;

  if (argc != 3) {
    printf("Usage: %s <IP> <Port>\n", argv[0]);
    exit(1);
  }

  clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (clnt_sock == -1) {
    error_message("socket() error!");
  }

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_adr.sin_port = htons(atoi(argv[2]));

  if (connect(clnt_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))) {
    error_message("connect() error!");
  } else {
    fputs("-> Connected...\n", stdout);
  }

  fputs("-> Operand Count: ", stdout);
  scanf("%d", &op_number);

  message[0] = (char)op_number;

  for (int i = 0; i < op_number; i ++) {
    printf("-> Operand %d: ", i + 1);
    scanf("%d", (int*)&message[i*OP_SIZE + 1]);
  }

  fgetc(stdin);
  fputs("-> Operator: ", stdout);
  scanf("%c", &message[op_number*OP_SIZE + 1]);
  write(clnt_sock, message, op_number*OP_SIZE + 2);

  read(clnt_sock, &result, RES_SIZE);

  printf("->: result is %d\n", result);
  close(clnt_sock);
  return EXIT_SUCCESS;
}














