#include <stdio.h>

int main() {
  char **s;
  char foo[] = "Hello World";

  // change 1: we should not dereference s variable
  s = "foo";
  printf("s is %s\n", s);

  // change 2: we should allocate memory for variable s
  s = malloc(sizeof(char *) * 1);
  s[0] = foo;
  printf("s[0] is %s\n", s[0]);
  return (0);
}