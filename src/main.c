#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  
  char inBuffer[64];
  // REPL Loop
  for (;;) {
    printf("$ ");
    fflush(stdout);
    fgets(inBuffer, 64, stdin);

    if(!strncmp(inBuffer, "exit\n", 64)) break;

    pid_t childPid = fork();

    if(!childPid) { // Child
      execvp("asdha", NULL);
      perror("execvp");
      break;
    } else if (pid >  0) { // Parent
      wait(NULL);
    } else {
      perror("fork");
    }

  }

  return 0;
}
