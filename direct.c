/*direct.c: traverses directories and gets the needed data*/

#include "direct.h"


void traverse(char *pathname, int outfd, int flags) {
   struct dirent *entry;
   struct stat curr;
   DIR *dp;

   chdir(pathname);

   if ((dp = opendir("./")) == NULL) {
      perror("traverse");
      exit(EXIT_FAILURE);
   }

   while ((entry = readdir(dp)) != NULL) {
      if (lstat(entry->d_name, &curr) == -1) {
         perror("traverse");
         exit(EXIT_FAILURE);
      }

      if (S_IFDIR(curr.st_mode)) {
         strcat(pathname, entry->d_name);
         strcat(pathname, "/");
         /*print path name if verbose is used*/
         if (flags == 0 || flags == 1) {
            printf("%s", pathname);
         }

         create_archive_entry(pathname, 2, flags);

         traverse(pathname, outfd, flags);
      }
      else if(S_IFREG(curr.st_mode)) {
         strcat(pathname, entry->d_name);
         /*print path name if verbose is used*/
         if (flags == 0 || flags == 1) {
            printf("%s", pathname);
         }

         create_archive_entry(pathname, 0, flags);
      }
      else if(S_IFLNK(curr.st_mode)) {
         strcat(pathname, entry->d_name);
         /*print path name if verbose is used*/
         if (flags == 0 || flags == 1) {
            printf("%s", pathname);
         }

         create_archive_entry(pathname, 1, flags);
      }
   }
}

/*
void traverse(char *pathname, int flags) {
   struct dirent entry;
   struct stat curr;
   DIR *dp;
   int offset = 0;

   if ((dp = opendir("./")) == NULL) {
      perror("traverse");
      exit(EXIT_FAILURE);
   }

   offset = telldir(dp);

   while ((entry = readdir(dp)) != NULL) {
      if (lstat(entry->d_name, &curr) == -1) {
         perror("traverse");
         exit(EXIT_FAILURE);
      }

      if (S_IFDIR(curr.st_mode)) {
         strcat(pathname, entry->d_name);
         strcat(pathname, "/");
         if (flags == 0 || flags == 1) {
            printf("%s", pathname);
         }

         create_archive_entry(pathname, 2, flags);

         traverse(pathname);
      }
   }

   seekdir(dp, offset);

   while ((entry = readdir(dp)) != NULL) {
      if (lstat(entry->d_name, &curr) == -1) {
         perror("traverse");
         exit(EXIT_FAILURE);
      }

      if (S_IFREG(curr.st_mode)) {
         strcat(pathname, entry->d_name);
         if (flags == 0 || flags == 1) {
            printf("%s", pathname);
         }

         create_archive_entry(pathname, 0, flags);

   if ((entry = readdir(dp)) != NULL)



   printf("boy!");
}
if ((dp = opendir("./")) == NULL) {
      perror("mypwd");
      exit(EXIT_FAILURE);
   }

   while ((entry = readdir(dp)) != NULL) {
      if (stat(entry->d_name, &curr) == -1) {
         perror("mypwd");
         exit(EXIT_FAILURE);
      }

      if (curr.st_ino == inodes[i - 1].st_ino && 
          curr.st_dev == inodes[i - 1].st_dev) {
         chdir(entry->d_name);
         break;
      }
   }

   if (stat("./", &curr) == -1) {
         perror("mypwd");
         exit(EXIT_FAILURE);
   }
}
*/
