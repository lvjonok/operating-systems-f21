#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>

struct rusage usage;

int main() {
  for (int s = 0; s < 10; s++) {
    char *arr = (char *)malloc(10 * 1024 * 1024);
    memset(arr, 0, 10 * 1024 * 1024);

    getrusage(RUSAGE_SELF, &usage);
    printf("%d\n", usage.ru_maxrss);

    sleep(1);
  }
}