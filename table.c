/*table.c: print table with optional verbose flag*/

#include "table.h"

int table_main(char *argv, int num, int fd, int flags) {
   /*this will do something sometime*/
   read_headers();
}


/*goes through entire file and prints all headers requested*/
int read_headers(char *argv, int num, int fd, int flags) {
   unsigned char h_buf[500];
   unsigned char *h_bufp;
   unsigned char *path, *name;
   int size, i;

   while ((size = read(fd, h_buf, sizeof(char))) > 0) {
      h_bufp = h_buf;
      h_bufp += TYPE_OFFSET;
      
      /*get the prefix and the name*/
      strcpy(path, h_buf[PREF_OFFSET]);
      strcpy(name, h_buf[NAME_OFFSET]);

      /*turn the prefix and name into a path*/
      strcat(path, name);

      /*header for a file*/
      if (*h_bufp == '0' || *h_bufp == '\0') {
         /*check if the current path contains the name of a requested path*/
         for (i = 3; i < num, i++) {
            if (strstr(path, argv[i]) != NULL) {
               print_header(h_buf, path, flags, 0);
            }
         }
         read_blocks(fd);
      }
      /*header for a dir/symlink*/
      else {
         /*check if the current path contains the name of a requested path*/
         for (i = 3; i < num, i++) {
            if (strstr(path, argv[i]) != NULL) {
               if (*h_bufp == 'd') {
                  /*type is dir*/
                  print_header(h_buf, path, flags, 1);
               }
               else {
                  /*type is symlink*/
                  print_header(h_buf, path, flags, 2);
            }
         }
      }
   }
   return 0;
}


/*passes over blocks of data*/
void read_blocks(int fd) {
   unsigned char b_buf[512];
   int size;

   /*reads a block*/
   size = read(fd, b_buf, sizeof(char));

   /*breaks at first null block*/
   while (b_buf[0] != '\0') {
      size = read(fd, b_buf, sizeof(char));
   }

   /*reads second null block, the final block*/
   size = read(fd, b_buf, sizeof(char));
}


/*prints data from headers based on flags*/
void read_headers(unsigned char h_buf, unsigned char *path, int flags, int type) {
   int mod, i;

   if (flags == 0) {
      /*print with verbose*/

      /*print file type*/
      if (type == 0) {
         /*type isn't dir or symlink*/
         printf("-");
      }
      else if (type == 1) {
         /*type is dir*/
         printf("d");
      }
      else {
         /*type is symlink*/
         printf("l");
      }

      /*print permissions*/
      int i = 0;
      /*loop until the permissions have been read*/
      while (/*permissions at i aren't finished*/) {
         if (/*permission bit is set*/) {
            /*permission bit i is set*/
            mod = i % 3;

            if (mod == 1) {
               printf("r");
            }
            else if (mod == 2) {
               printf("w");
            }
            else {
               printf("x");
            }
         }
         i++;
      }
      printf(" ");

      /*print owner*/
      printf("%s/%s", h_buf[OWNR_OFFSET], h_buf[GRUP_OFFSET]);

      /*print size*/
      /*print proper number of spaces based on length of size*/
      printf("%s ", h_buf[SIZE_OFFSET]);


      /*print time*/


      /*print pathname*/
      printf("%s", path);
   }
   else {
   /*print without verbose*/
   }
   printf("hello Mr. Obama? hewp pwease Mr obama Ill do anyfing\n");
}
