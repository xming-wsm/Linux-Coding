#include <stdio.h>
#include <sys/uio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
  struct iovec vec[2];
  char buf1[] = "abcdefg";
  char buf2[] = "1232132";
  int bytes = 0;

  vec[0].iov_base = buf1;
  vec[0].iov_len = 3;
  vec[1].iov_base = buf2;
  vec[1].iov_len = sizeof(buf2);

  bytes = writev(1, vec, 2);
  puts("");
  printf("Write bytes: %d\n", bytes);

  return EXIT_SUCCESS;
}
