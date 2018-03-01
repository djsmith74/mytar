/*table.c: print table with optional verbose flag*/

#include "table.h"

int table_main(char *argv[], int num, int fd, int flags) {
   /*this will do something sometime*/
   read_headers(argv, num, fd, flags);
   return 0;
}


/*goes through entire file and prints all headers requested*/
int read_headers(char *argv[], int num, int fd, int flags) {
   unsigned char h_buf[512];
   unsigned char *h_bufp;
   unsigned char *path, *name;
   char **endptr = NULL;
   int i, k;

   path = NULL;
   name = NULL;

   if ((path = calloc(100, sizeof(char))) == NULL) {
         perror("bad calloc");
         exit(EXIT_FAILURE);
      }

      if ((name = calloc(155, sizeof(char))) == NULL) {
         perror("bad calloc");
         exit(EXIT_FAILURE);
      }

   k = 0;

   while (read(fd, &h_buf, sizeof(char) * 512) > 0) {
      /*if ((path = calloc(100, sizeof(char))) == NULL) {
         perror("bad calloc");
         exit(EXIT_FAILURE);
      }

      if ((name = calloc(155, sizeof(char))) == NULL) {
         perror("bad calloc");
         exit(EXIT_FAILURE);
      }*/
      /*printf(" \n%s\n ", h_buf);*/
 
      h_bufp = h_buf + PREF_OFFSET;
      strcpy((char*)path, (char*)h_bufp);
      /*get the prefix and the name*/
      /*strcpy((char*)path, (char*)&h_buf[PREF_OFFSET]);*/
      /*strcpy((char*)name, (char*)&h_buf[NAME_OFFSET]);*/


      h_bufp = h_buf + NAME_OFFSET;
      /*printf("number: %d: %s ", k, h_buf);*/
      strcpy((char*)name, (char*)h_bufp);

      /*strcpy((char*)name, (char*)(h_buf + NAME_OFFSET));*/
      /*turn the prefix and name into a path*/
      strcat((char*)path,(char*)name);
      /*printf(" name %d: %s", k, name);*/


      h_bufp = h_buf + TYPE_OFFSET;
      /*header for a file*/
      if (*h_bufp == '0' || *h_bufp == '\0') {
         /*printf("header %d, REG\n", k);*/
         /*check if the current path contains the name of a requested path*/
         for (i = 3; i < num; i++) {
            if (strstr((char*)path, argv[i]) != NULL) {
               print_header(h_buf, path, flags, 0);
            }
         }
         if (strtol((char*)&h_buf[SIZE_OFFSET], endptr, 8) != 0) {
            /*printf("made it!\n");*/
            read_blocks(fd, strtol((char*)&h_buf[SIZE_OFFSET], endptr, 8));
         }
      }
      /*header for a dir/symlink*/
      else {
         /*check if the current path contains the name of a requested path*/
         for (i = 3; i < num; i++) {
            if (strstr((char*)path, argv[i]) != NULL) {
               if (*h_bufp == '5') {
                  /*printf("header %d, DIR\n", k);*/
                  /*type is dir*/
                  print_header(h_buf, path, flags, 1);
               }
               else {
                  /*type is symlink*/
                  /*printf("header %d, SYM\n", k);*/
                  print_header(h_buf, path, flags, 2);
               }
               break; /*TODO might be wrong*/
            }
         }
      }
      k++;
   }
   return 0;
}


/*passes over blocks of data*/
void read_blocks(int fd, long int size) {
   unsigned char b_buf[512];
   int reads = size / 512;

   /*reads a block*/
   read(fd, &b_buf, sizeof(char) * 512);

   /*breaks at first null block*/
   while (reads > 0) {
      /*printf("daberoni\n");*/
      read(fd, &b_buf, sizeof(char) * 512);
      reads--;
   }
}


/*prints data from headers based on flags*/
void print_header(unsigned char *h_buf, unsigned char *path,
                  int flags, int type) {
   long int size;
   char owner[32];
   char group[32];
   char **endptr = NULL;

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
      else if (type == 2){
         /*type is symlink*/
         printf("l");
      }

      /*print permissions*/
      print_perms((char*)&h_buf[MODE_OFFSET]);
      /*i = 0;
      snprintf(permissions, 10, "%09o", h_buf[MODE_OFFSET]);
      while (i < 9) {
         printf("%c\n", permissions[i]);
         if (permissions[i] == '1') {
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
         else {
            printf("-");
         }
         i++;
      }
      */
      printf(" ");

      /*print owner*/
      snprintf(owner, 32, "%s", (char*)&h_buf[OWNR_OFFSET]);
      snprintf(group, 32, "%s", (char*)&h_buf[GRUP_OFFSET]);
      printf("%s/%s", owner, group);

      /*print size*/
      /*print proper number of spaces based on length of size*/
      size = strtol((char*)&h_buf[SIZE_OFFSET], endptr, 8);
      printf("%9lu ", size);


      /*print time*/
      print_time(strtol((char*)&h_buf[TIME_OFFSET], endptr, 8));

      /*print pathname*/
      printf("%s\n", path);

   }
   else {
   /*print without verbose*/

      /*print pathname*/
      printf("%s\n", path);
   }
}

void print_perms(char *oct) {
   int i = 4;
   char c;

   for (; i < 7; i++) {
      c = oct[i];
      switch(c) {
         case '1':
            printf("--x");
            break;
         case '2':
            printf("-w-");
            break;
         case '3':
            printf("-wx");
            break;
         case '4':
            printf("r--");
            break;
         case '5':
            printf("r-x");
            break;
         case '6':
            printf("rw-");
            break;
         case '7':
            printf("rwx");
            break;
         default :
            printf("---");
      }
   }
}


/*will print the time string*/
void print_time(long int time) {
   char time_str[18];
   time_t t = (time_t)time;

   strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M ", localtime(&t));

   printf("%s", time_str);
}
