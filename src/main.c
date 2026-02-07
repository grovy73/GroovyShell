#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int countWords(char* src) {
  int count = 1;
  int shouldCountSpace;
  int haveEncounteredLetter = 0;
  for(int i = 0; src[i]; i++) {
    if(!haveEncounteredLetter && src[i] > 32 && src[i] < 127) {haveEncounteredLetter = 1;}
    shouldCountSpace = src[i] == ' ' && i != 0 && src[i + 1] != ' ' && src[i + 1] != '\0' && haveEncounteredLetter;

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
    dest[i++] = word;
    word = strtok(NULL, " ");
  }
}

int main(int argc, char *argv[]) {
  char inBuffer[64];
  // REPL Loop
  for (;;) {
    printf("$ ");
    fflush(stdout);
    fgets(inBuffer, 64, stdin);

    if(!strncmp(inBuffer, "exit\n", 64)) break;
    
    int argsSize = countWords(inBuffer);
    char* args[argsSize];
    parseArgs(inBuffer, args);
  }

  return 0;
}
