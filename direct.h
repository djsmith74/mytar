#ifndef DIRECT_H
#define DIRECT_H

#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

#define _XOPEN_SOURCE 500

void traversal_nftw(char *path);

int nftw_function(char *path, struct stat *buf, int fileflags, struct FTW *ftw);

#endif
