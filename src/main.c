#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  
  char inBuffer[64];
  // REPL Loop
  for (;;) {
    printf("$ ");
    fflush(stdout);
    fgets(inBuffer, 64, stdin);

    if(!strncmp(inBuffer, "exit\n", 64)) break;
  }

  return 0;
}
