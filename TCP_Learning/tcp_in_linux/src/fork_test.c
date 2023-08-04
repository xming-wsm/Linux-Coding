#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int test = 1;


int main(int argc, char *argv[])
{
  pid_t pid_value;
  pid_value = fork();

  if (pid_value == 0) {
    printf("child process: %d\t%p\n", test, &test);
    test = 2;
    printf("child process: %d\t%p\n", test, &test);
  } else {
    printf("par rocess: %d\t%p\n", test, &test);

    sleep(2);
    printf("par rocess: %d\t%p\n", test, &test);
  }


  return EXIT_SUCCESS;
}
