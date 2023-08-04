#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>


#define BUF_SIZE 1024
#define OP_SIZE 4
#define PORT 9121


void error_message(char* msg);
int calculate(int op_number, int op_array[], char operation);


int main(int argc, char *argv[])
{
  // if (argc != 2) {
  //   printf("Input require: %s <Port>\n", argv[0]);
  //   exit(1);
  // }

  struct sockaddr_in server_addr, clnt_addr;
  char message[BUF_SIZE];
  int serv_sock, clnt_sock; // The handel of socket
  int op_number, result;
  int recv_cnt, recv_len;
  socklen_t clnt_adr_sz;
  char* ip_server;
  char* ip_temp;



  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == -1) {
    error_message("socket() error");
  }

  int flag = 1;
  setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));


  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

  if (bind(serv_sock, (struct sockaddr*)&server_addr, sizeof(server_addr))== -1) {
    error_message("bind() error");
  }
  ip_temp = inet_ntoa(server_addr.sin_addr);
  strcpy(ip_server, ip_temp);
  printf("Server Open Succes, IP: %s\n", ip_server);



  if (listen(serv_sock, 5) == -1) {
    error_message("listen() error");
  }

  clnt_adr_sz = sizeof(clnt_addr);

  for (int i = 0; i < 1; i ++) {
    op_number = 0;
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_adr_sz);

    read(clnt_sock, &op_number, 1); // obtain the number of operation

    recv_len = 0;
    while ((op_number * OP_SIZE + 1) > recv_len) {
      recv_cnt = read(clnt_sock, &message[recv_len], BUF_SIZE - 1);
      recv_len += recv_cnt;
    }
    result = calculate(op_number, (int *)message, message[recv_len - 1]);
    write(clnt_sock, &result, sizeof(result));
    close(clnt_sock);
  }

  close(serv_sock);
  return EXIT_SUCCESS;
}




int calculate(int op_number, int op_array[], char operation) {
  int result = op_array[0], i;
  switch (operation) {
    case '+':
      for (i = 1; i < op_number; i ++) result += op_array[i];
      break;
    case '-':
      for (i = 1; i < op_number; i ++) result -= op_array[i];
      break;
    case '*':
      for (i = 1; i < op_number; i ++) result *= op_array[i];
      break;
  }
  return result;
}


void error_message(char* msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
