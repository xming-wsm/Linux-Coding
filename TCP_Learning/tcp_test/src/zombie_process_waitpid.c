#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  int status;
  pid_t pid = fork();

  if (pid == 0) {
    sleep(15);
    return 24;
  } else {
    while (!waitpid(-1, &status, WNOHANG)) {
      sleep(3);
      fputs("Sleep 3sec\n", stderr);
    }

    if (WIFEXITED(status)) {
      printf("Child Process send %d \n", WEXITSTATUS(status));
    }
  }

  return EXIT_SUCCESS;
}
