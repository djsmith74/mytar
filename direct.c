/*direct.c: traverses directories and gets the needed data*/

#include <ftw.h>
#include "direct.h"

/*void traverse_nftw(char *path) {
   struct stat buf;
   int ret;
   int flags = FTW_CHDIR | FTW_MOUNT | FTW_PHYS;


   ret = nftw(path, nftw_funtion, 5, flags);
}

int nftw_function(char *path, struct stat *buf, int fileflags, struct FTW *ftw) {
   printf("hello world!");
   return 0;
}
*/
int start_traverse(char *path){
   struct stat curr;

   if (lstat("./", &curr) == -1) {
      perror("start_traverse");
      exit(EXIT_FAILURE);
   }

void traverse(struct stat curr, char *pathname, int flags) {
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
         strcat(pathname, "/");
         strcat(pathname, entry->d_name);
         /*print path name if verbose is used*/
         if (flags == 0 || flags == 1) {
            printf("%s", pathname);
         }

         traverse(pathname);
      }
   }

   /*return to beginning of directory*/
   seekdir(dp, offset);

   while ((entry = readdir(dp)) != NULL) {
      if (lstat(entry->d_name, &curr) == -1) {
         perror("traverse");
         exit(EXIT_FAILURE);
      }

      if (S_IFREG(curr.st_mode)) {
         /*add to pathname and call create on it*/

   if ((entry = readdir(dp)) != NULL)




int traverse(void) {
   struct stat curr;
   struct dirent entry;
   DIR *dp;

   if (lstat("./", &curr) == -1) {
      perror("traverse");
      exit(EXIT_FAILURE);
   }
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
