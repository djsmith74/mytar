#ifndef DIRECT_H
#define DIRECT_H

#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "create.h"

void traverse(char *pathname, int outfd, int flags);

#endif
