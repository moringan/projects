#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int wstatus;
  pid_t pid = fork();

  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    // Child process
    char *argv[] = {"non_existent_command", NULL};
    if (execvp(argv[0], argv) == -1) {
      perror("execvp");
      _exit(EXIT_FAILURE);
    }
  } else {
    // Parent process
    if (wait(&wstatus) == -1) {
      perror("wait");
      exit(EXIT_FAILURE);
    }

    if (WIFEXITED(wstatus)) {
      printf("Child exited with status %d\n", WEXITSTATUS(wstatus));
    } else if (WIFSIGNALED(wstatus)) {
      printf("Child killed by signal %d\n", WTERMSIG(wstatus));
    }
  }

  return 0;
}
