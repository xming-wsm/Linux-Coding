#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>



void sig_childprocess_callback(int sig) {
  int status;
  pid_t id = waitpid(-1, &status, WNOHANG);
  if (WIFEXITED(status)) {
    printf("Removed process ID: %d\n", id);
    printf("Child Return value: %d\n", WEXITSTATUS(status));
  }
}

int main(int argc, char *argv[])
{
  pid_t pid;
  struct sigaction sig_act;
  sig_act.sa_handler = sig_childprocess_callback;
  sigemptyset(&sig_act.sa_mask);
  sig_act.sa_flags = 0;
  sigaction(SIGCHLD, &sig_act, 0);

  pid = fork();
  if (pid == 0) {
    fputs("Child Process\n", stdout);
    sleep(10);
    return 12;
  } else {
    printf("Child Process ID: %d\n", pid);
    pid = fork();

    if (pid == 0) {
      fputs("Child Process\n", stdout);
      sleep(10);
      return 24;
    } else {
      printf("Child Process ID: %d\n", pid);
      for (int i = 0; i < 5; i ++) {
        fputs("Wait...\n", stdout);
        sleep(5);
      }

    }

  }

  return EXIT_SUCCESS;
}
