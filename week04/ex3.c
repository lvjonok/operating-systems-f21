#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  printf("This is simple shell, white `exit` to stop its execution\n");
  while (1) {
    char* cmd = malloc(sizeof(char) * 256);
    scanf("%s", cmd);
    if (!strcmp(cmd, "exit")) break;
    system(cmd);
  }
  return 0;
}