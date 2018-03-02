/*table.c: print table with optional verbose flag*/

#include "table.h"

int table_main(char *argv[], int argc, int fd, int flags) {
   /*this will do something sometime*/
   read_headers(argv, argc, fd, flags);
   return 0;
}


/*goes through entire file and prints all headers requested*/
int read_headers(char *argv[], int argc, int fd, int flags) {
   unsigned char h_buf[512];
   unsigned char *h_bufp;
   unsigned char *path, *name, *pref;
   char **endptr = NULL;
   int i, k;
   int chksum;

   path = NULL;
   name = NULL;
   pref = NULL;

   if ((pref = calloc(155, sizeof(char))) == NULL) {
      perror("bad calloc");
      exit(EXIT_FAILURE);
   }

   if ((name = calloc(100, sizeof(char))) == NULL) {
      perror("bad calloc");
      exit(EXIT_FAILURE);
   }

   if ((path = calloc(255, sizeof(char))) == NULL) {
      perror("bad calloc");
      exit(EXIT_FAILURE);
   }

   while (read(fd, &h_buf, sizeof(char) * 512) > 0) {

      /*check if null block*/
      if (h_buf[0] == '\0') {
         return 0;
      }
 
      /*chksum check to see if header is good*/
      k = 0;
      chksum = 0;
      /*read before chksum field*/
      for (; k < CHKS_OFFSET; k++) {
         chksum += h_buf[k];
      }

      /*read after chksum field*/
      for (k = CHKS_OFFSET + 8; k < 512; k++) {
         chksum += h_buf[k];
      }

      /*add 8 spaces for chksum field*/
      for (k = 0; k < 8; k++) {
         chksum += ' ';
      }

      h_bufp = h_buf + CHKS_OFFSET;
      /*printf("Header check: %lu\n", strtol((char*)h_bufp, endptr, 8));*/
      /*printf("Counted check: %d\n", chksum);*/
      if (strtol((char*)h_bufp, endptr, 8) != chksum) {
         perror("Invalid header\n");
         exit(EXIT_FAILURE);
      }

      /*get the prefix*/
      h_bufp = h_buf + PREF_OFFSET;
      strcpy((char*)pref, (char*)h_bufp);

      h_bufp = h_buf + NAME_OFFSET;
      strcpy((char*)name, (char*)h_bufp);

      if (pref[0] == '\0') {
         /*turn the prefix and name into a path*/
         strcat((char*)path,(char*)name);
      }
      else {
         strcat((char*)path,(char*)pref);
         strcat((char*)path,(char*)name);
      }


      h_bufp = h_buf + TYPE_OFFSET;
      /*header for a file*/
      if (*h_bufp == '0' || *h_bufp == '\0') {
         if (argc > 3) {
            /*check if the current path contains the name of a requested path*/
            for (i = 3; i < argc; i++) {
               if (strstr((char*)path, argv[i]) != NULL) {
                  print_header(h_buf, path, flags, 0);
               }

               if (strtol((char*)&h_buf[SIZE_OFFSET], endptr, 8) != 0) {
                 /*printf("made it!\n");*/
                 read_blocks(fd, strtol((char*)&h_buf[SIZE_OFFSET], endptr, 8));
               }
            }
         }
         else {
            print_header(h_buf, path, flags, 0);
            if (strtol((char*)&h_buf[SIZE_OFFSET], endptr, 8) != 0) {
               /*printf("made it!\n");*/
               read_blocks(fd, strtol((char*)&h_buf[SIZE_OFFSET], endptr, 8));
            }
         }
      }
      /*header for a dir/symlink*/
      else {
         if (argc > 3) {
            /*check if the current path contains the name of a requested path*/
            for (i = 3; i < argc; i++) {
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
         else {
            if (*h_bufp == '5') {
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
