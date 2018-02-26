/*direct.c: traverses directories and gets the needed data*/

#include <ftw.h>
#include "direct.h"

void traverse_nftw(char *path) {
   struct stat buf;
   int ret;
   int flags = FTW_CHDIR | FTW_MOUNT | FTW_PHYS;


   ret = nftw(path, nftw_funtion, 5, flags);
}

int nftw_function(char *path, struct stat *buf, int fileflags, struct FTW *ftw) {
   printf("hello world!");
   return 0;
}

int traverse(char *path) {
   printf("boy!");
}
