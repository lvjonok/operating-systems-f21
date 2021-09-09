#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int n;

int main() {
  fork() ? printf("Hello from parent [%d - %d]\n", getpid(), n++)
         : printf("Hello from child [%d - %d]\n", getpid(), n++);
}