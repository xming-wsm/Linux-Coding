#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 50

int main(int argc, char *argv[])
{
  int fds1[2], fds2[2]; // create the file handle of pipe1 and pipe2 
  char str1[] = "Hello";
  char str2[] = "Thanks for your message.";
  char msg[BUF_SIZE];

  pid_t pid;

  pipe(fds1);
  pipe(fds2);

  pid = fork();

  if (pid == 0) {
    // child process
    write(fds1[1], str1, sizeof(str1));
    read(fds2[0], msg, BUF_SIZE);
    printf("Child process output: %s\n", msg);
  } else {
    // father process
    read(fds1[0], msg, BUF_SIZE);
    printf("Parent process output: %s\n", msg);
    write(fds2[1], str2, sizeof(str2));
  }

  return EXIT_SUCCESS;
}
