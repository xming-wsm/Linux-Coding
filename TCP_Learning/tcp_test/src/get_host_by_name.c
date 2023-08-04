#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>


void error_msg(char* msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <addr>\n", argv[0]);
  }

  struct hostent* host;
  host = gethostbyname(argv[1]);
  if (host == NULL) {
    error_msg("gethostbyname() error");
  }


  // official name
  printf("Official name: %s\n", host->h_name);

  // alias list
  for (int i = 0; host->h_aliases[i] != NULL; i ++) {
    printf("Alias%d: %s\n", i + 1, host->h_aliases[i]);
  }

  // host address type
  printf("Host address type: %s\n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

  // list of adress from name server
  for (int i = 0; host->h_addr_list[i] != NULL; i ++) {
    printf("IP addr %d: %s\n", i + 1, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
  }


  return EXIT_SUCCESS;
}

















