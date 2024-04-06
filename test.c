#include "stdio.h"
int main(int argc, char* argv[]) {
  int a = 10;
  if (argc == 3) {
      a = 15;
      printf("Salto 1, a = %d", a);
  }
  else {
      a++;
      printf("Salto 2, a = %d", a);
  }
  printf("Hello, World! %d", a);
  return 0;
}
