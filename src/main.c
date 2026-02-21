#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

char* handleTilde(char* arg) {
  char* home = getenv("HOME");
  if(!home) {
    return strdup(arg);
  }
  if(arg[1] == '\0') return strdup(home);

  if(arg[1] == '/') {
    int len = strlen(home) + strlen(arg);
    char* result = malloc(len);
    sprintf(result, "%s%s", home, arg + 1);
    return result;
  }

  return strdup(arg);
}

void removeFinalNewline(char *src) {
  int srcLen = strlen(src);
  if(srcLen <= 0) return;
  if(src[srcLen - 1] != '\n') {
    return;
  }
  src[srcLen - 1] = 0;
}

int countWords(char* src) {
  int count = 1;
  int shouldCountSpace;
  int haveEncounteredLetter = 0;
  for(int i = 0; src[i]; i++) {
    if(!haveEncounteredLetter && src[i] > 32 && src[i] < 127) {haveEncounteredLetter = 1;}
    shouldCountSpace = src[i] == ' ' && i != 0 && src[i + 1] != ' ' && src[i + 1] != '\0' && src[i + 1] != '\n' && haveEncounteredLetter;

    if(shouldCountSpace) {
      count++;
    }
  }
  if(!haveEncounteredLetter) {count = 0;}
  return count;
}

void parseArgs(char* src, char** dest) {
  char* word = strtok(src, " ");

  int i = 0;
  while(word) {
    removeFinalNewline(word);
    dest[i++] = word;
    word = strtok(NULL, " ");
  }
  dest[i] = NULL;
}

int main(void) {
  char inBuffer[64];
  // REPL Loop
  for (;;) {
    printf("$ ");
    fflush(stdout);
    if(!fgets(inBuffer, 64, stdin)) break;

    int argsSize = countWords(inBuffer);

    if(argsSize <= 0) {
      continue;
    }

    char* args[argsSize + 1];
    parseArgs(inBuffer, args);
    
    // BULTINS
    if(!strncmp(args[0], "exit", 5)) break;
    if(!strncmp(args[0], "cd", 3)) {
      char* toDir = args[1];
      if(args[1][0] == '~') {
        toDir = handleTilde(args[1]);
      }

      if(chdir(toDir) != 0) {
        perror("cd");
      }
      continue;
    }

    pid_t pid = fork();

    switch(pid) {
      case -1:
        perror("fork");
        exit(EXIT_FAILURE);
      case 0:
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_SUCCESS);
      default:
        wait(NULL);
        break;
    }
  }

  return 0;
}
