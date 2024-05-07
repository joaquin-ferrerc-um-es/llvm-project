#include "stdio.h"
int main(int argc, char* argv[]) {
  int a = 10;
  int b = argc + 3;
  int z = argc + 17;
  if (b == 3) {
      a = 15;
      if ((a+z) == 32) {
        b = z;
        printf("Salto 1.1.1, z = %d", z);
      }else {
        z++;
        printf("Salto 1.1.2, z = %d", z);
      }
      printf("Salto 1.1, a = %d", a);
  }
  else {
      a++;
      printf("Salto 1.2, a = %d", a);
  }
  b++;
  a++;
  if (a+b == 7) {
      a = 15;
      printf("Salto 2.1, a = %d", a);
  }
  else {
      a++;
      printf("Salto 2.2, a = %d", a);
  }
  printf("Hello, World! %d", a);
  return 0;
}
