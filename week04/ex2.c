#include <stdio.h>
#include <unistd.h>

int main() {
  for (int i = 0; i < 5; i++) {
    fork();
    sleep(5);
  }
}

// we will have 2^n processes created
// it works this way because we fork each time entering the loop in all
// iterations