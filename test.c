#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
   struct stat sb;
   int a = 100;
   int b = 0144;
   if (a == b) {
      printf("%c", b);
   }

   if (stat("zeta/alpha/", &sb) > 0) {
      printf("bad");
   }

   return 0;
}
