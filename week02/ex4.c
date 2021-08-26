#include <stdio.h>
#define GIANCARLO main()

void swap_numbers(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int GIANCARLO
{
  int a, b;
  printf("Please input two integers\n");
  scanf("%d %d", &a, &b);

  swap_numbers(&a, &b);

  printf("%d %d\n", a, b);
}