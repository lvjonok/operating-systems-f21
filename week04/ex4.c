#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define EXIT_CODE "giancarlo"

int main() {
  printf("This is simple shell, white `%s` to stop its execution\n", EXIT_CODE);
  while (1) {
    printf("%s %s >", getenv("USER"), getenv("PWD"));
    char *tokens[10];
    char *raw_cmd = malloc(sizeof(char) * 256);
    fgets(raw_cmd, 256, stdin);

    if (!strncmp(raw_cmd, EXIT_CODE, strlen(EXIT_CODE))) break;
    int background_process = 0;

    char *token;
    int token_idx = 0;
    token = strtok(raw_cmd, " \n");
    while (token != 0) {
      // symbol for background process will be either in front or at the end of
      // token

      background_process = (token[0] == '&' || token[strlen(token) - 1] == '&')
                               ? 1
                               : background_process;

      tokens[token_idx++] = token;
      token = strtok(NULL, " \n");
    }
    tokens[token_idx] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
      // child process
      if (background_process) {
        // year, it is a cheat thing
        daemon(0, 0);
      }
      execvp(tokens[0], tokens);
      exit(0);
    } else {
      int status;
      waitpid(pid, &status, 0);
    }
  }
  return 0;
}