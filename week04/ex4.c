#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXIT_CODE "giancarlo"

int main() {
  printf("This is simple shell, white `%s` to stop its execution\n", EXIT_CODE);
  char* cmd = malloc(sizeof(char) * 256);
  while (1) {
    free(cmd);
    cmd = malloc(sizeof(char) * 256);
    fgets(cmd, 256, stdin);
    if (!strncmp(cmd, EXIT_CODE, strlen(EXIT_CODE))) break;
    if (fork() == 0) {
      system(cmd);
      exit(0);
    }
  }
  return 0;
}