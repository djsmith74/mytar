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
               print_header(h_buf, flags);
            }
         }
         read_blocks(fd);
      }
      /*header for a dir/symlink*/
      else {
         /*check if the current path contains the name of a requested path*/
         for (i = 3; i < num, i++) {
            if (strstr(path, argv[i]) != NULL) {
               print_header(h_buf, flags);
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
void read_headers(unsigned char h_buf, int flags) {
   printf("hello Mr. Obama? hewp pwease Mr obama Ill do anyfing\n");
}
