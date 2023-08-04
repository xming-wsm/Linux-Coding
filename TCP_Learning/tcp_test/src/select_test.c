#include <stdlib.h>
#include <sys/select.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 50


int main(int argc, char *argv[])
{
  fd_set reads, temps;
  int result_select, str_len;
  char buf[BUF_SIZE];
  struct timeval timeout;

  FD_ZERO(&reads);
  FD_SET(0, &reads);

  while (1) {
    temps = reads;
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;
    result_select = select(1, &temps, 0, 0, &timeout);

    if (result_select == -1) {
      fputs("select() error\n", stderr);

    } else if (result_select == 0) {
      fputs("timeout\n", stdout);

    } else {
      if (FD_ISSET(0, &temps)) {
        str_len = read(0, buf, BUF_SIZE);
        buf[str_len - 1] = '\0';
        printf("message from stdin: %s\n", buf);
      }
    }
  }


  return EXIT_SUCCESS;
}
