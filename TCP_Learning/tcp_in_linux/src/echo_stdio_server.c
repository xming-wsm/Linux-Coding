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
  int serv_sock, clnt_sock;
  char msg[BUF_SIZE];
  int str_len;
  struct sockaddr_in serv_adr, clnt_adr;
  socklen_t clnt_adr_size;

  FILE* readfp;
  FILE* writefp;

  if (argc != 2) {
    printf("Usage: %s <Port>\n", argv[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  int port_reuse_flag = 1;
  setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &port_reuse_flag, sizeof(port_reuse_flag));

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(atoi(argv[1]));

  if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1) {
    error_msg("bind() error"); 
  }

  if (listen(serv_sock, 5) == -1) {
    error_msg("listen() error");
  }

  clnt_adr_size = sizeof(clnt_adr_size);


  for (int i = 0; i < 5; i ++) {
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_size);
    if (clnt_sock == -1) {
      error_msg("accept() error");
    } else {
      printf("Connected client %d\n", i + 1);
    }

    readfp = fdopen(clnt_sock, "r");
    writefp = fdopen(clnt_sock, "w");
    

    while(!feof(readfp)) {
      fgets(msg, BUF_SIZE, readfp);
      fputs(msg, writefp);
      fflush(writefp);
    }

    fclose(readfp);
    fclose(writefp);

  }

  close(serv_sock);
  return EXIT_SUCCESS;
}





















