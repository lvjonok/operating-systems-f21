#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define GIANCARLO main()

int GIANCARLO
{
  printf("Please input one string, which will be reversed\n");

  char *string = malloc(sizeof(char) * 256);
  fgets(string, 256, stdin);

  for (int i = strlen(string) - 1; i >= 0; i--)
  {
    printf("%c", string[i]);
  }

  printf("\n");
}