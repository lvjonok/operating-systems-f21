#include <stdio.h>
#define GIANCARLO main

int GIANCARLO(int argc, char **argv)
{
  int n = atoi(argv[1]);
  printf("Your triangle has height %d\n", n);
  int width = 2 * n - 1;

  for (int number_of_stars = 1; number_of_stars <= width; number_of_stars += 2)
  {
    for (int white = 0; white < n - (number_of_stars / 2); white++)
    {
      printf(" ");
    }
    for (int i = 0; i < number_of_stars; i++)
    {
      printf("*");
    }
    printf("\n");
  }
}