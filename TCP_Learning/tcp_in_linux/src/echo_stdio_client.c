#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/io.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024


void error_msg(char* msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}


int main(int argc, char *argv[])
{
  int sock;
  char msg[BUF_SIZE];
  int str_len;

  struct sockaddr_in serv_adr;
  FILE* readfp;
  FILE* writefp;

  if (argc != 3) {
    printf("Usage: %s <IP> <Port>\n", argv[0]);
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    error_msg("socket() error");
  }

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_adr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1) {
    error_msg("connect() error");
  } else {
    puts("Connected ...");
  }

  readfp = fdopen(sock, "r");
  writefp = fdopen(sock, "w");

  while (1) {

    fputs("Input message(Q to quit): ", stdout);
    fgets(msg, BUF_SIZE, stdin);
    if ( !(strcmp(msg, "q\n")) || !strcmp(msg, "Q\n"))
      break;

    fputs(msg, writefp);
    fflush(writefp);
    fgets(msg, BUF_SIZE, readfp);
    printf("Message from server: %s", msg);
  }
  fclose(writefp);
  fclose(readfp);

  return EXIT_SUCCESS;
}
