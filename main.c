/*main.c: handles all command line I/O, checking flags and executing*/
/*the proper functions*/

#include "main.h"
#include "direct.h"

int main(int argc, char *argv[]) {
   int flags[5] = {0};
   int ret = 0;

   /*check number of command line arguments*/
   if (argc < 3) {
      printf("Invalid number of arguments\n");
      exit(EXIT_FAILURE);
   }


   /*check the flags*/
   get_flags(argv[1], flags);

   if (flags[0] == 1) {
      if (flags[3] == 1 && flags[4] == 1) {
         /*create with verbose and strict*/
      }
      else if (flags[3] == 1) {
         /*create with verbose*/
      }
      else if (flags[4] == 1) {
         /*create with strict*/
      }
      else {
         /*create*/
         
      }
   }
   else if (flags[1] == 1) {
      if (flags[3] == 1) {
         /*print with verbose*/
      }
      else {
         /*print*/
      }
   }
   else if (flags[2] == 1) {
      /*extract*/
   }
   else {
      printf("Improper flags\n");
      exit(EXIT_FAILURE);
   }

   ret = traverse_nftw("./"); 

   return 0;
}

/*fills flags array based on the command line argument string*/
int *get_flags(char *c, int flags[]) {
   while (*c != '\0') {
      if (*c == 'c') {
         flags[0] = 1;
      }
      else if (*c == 't') {
         flags[1] = 1;
      }
      else if (*c == 'x') {
         flags[1] = 2;
      }
      else if (*c == 'v') {
         flags[1] = 3;
      }
      else if (*c == 'S') {
         flags[1] = 4;
      }
      c++;
   }
   return flags;
}
