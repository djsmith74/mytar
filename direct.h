#ifndef DIRECT_H
#define DIRECT_H

#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>


/*void traversal_nftw(char *path);

int nftw_function(char *path, struct stat *buf, int fileflags, struct FTW *ftw);
*/
int traverse(char *path);

#endif
