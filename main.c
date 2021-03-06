/*main.c: handles all command line I/O, checking flags and executing*/
/*the proper functions*/

#include "main.h"
#include "direct.h"

int main(int argc, char *argv[]) {
   int infd, outfd;
   int flags[5] = {0};

   /*check number of command line arguments*/
   if (argc < 3) {
      perror("Invalid number of arguments\n");
      exit(EXIT_FAILURE);
   }


   /*check the flags*/
   get_flags(argv[1], flags);

   if (flags[0] == -1) {
      /*printf("you must specify at least one of the 'ctx' options.\n");*/
      perror("Usage: mytar [ctxSp[f tarfile]] [file1 [ file2 [...] ] ]\n");
      return 1;
   }


   if (flags[0] == 1) {
      /*c flag*/

      outfd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT);
      if (outfd == -1) {
         perror(argv[2]);
         exit(EXIT_FAILURE);
      }

      if (flags[3] == 1 && flags[4] == 1) {
         /*create with verbose and strict*/
         create_main(argc, argv, outfd, 0); 
      }
      else if (flags[3] == 1) {
         /*create with verbose*/
         create_main(argc, argv, outfd, 1); 
      }
      else if (flags[4] == 1) {
         /*create with strict*/
         create_main(argc, argv, outfd, 2); 
      }
      else {
         /*create*/
         create_main(argc, argv, outfd, 3); 
         
      }
   }
   else if (flags[1] == 1) {
      /*t flag*/

      infd = open(argv[2], O_RDONLY);
      if (infd == -1) {
         perror(argv[1]);
         exit(EXIT_FAILURE);
      }

      if (flags[3] == 1) {
         /*print with verbose*/
         table_main(argv, argc, infd, 0);
      }
      else {
         /*print*/
         table_main(argv, argc, infd, 1);
      }
   }
   else if (flags[2] == 1) {
      /*extract*/
   }
   else {
      printf("Improper flags\n");
      exit(EXIT_FAILURE);
   }


   return 0;
}

/*fills flags array based on the command line argument string*/
int *get_flags(char *c, int flags[]) {
   int i = 0;
   while (*c != '\0') {
      if (*c == 'c') {
         flags[0] = 1;
      }
      else if (*c == 't') {
         flags[1] = 1;
      }
      else if (*c == 'x') {
         flags[2] = 1;
      }
      else if (*c == 'v') {
         flags[3] = 1;
      }
      else if (*c == 'S') {
         flags[4] = 1;
      }
      else if (*c == 'f') {
         /*do nothing*/
         ;
      }
      else {
         /*printf("unrecognized option: '%c'.\n", *c);*/
         i = 1;
      }
      c++;
   }
   if (i == 1) {
      flags[0] = -1;
   }
   return flags;
}
