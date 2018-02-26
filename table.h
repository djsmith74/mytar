#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define NAME_OFFSET 0
#define PREF_OFFSET 345
#define TYPE_OFFSET 156

int table_main(char *argv, int num, int fd, int flags);

int read_headers(char *argv, int num, int fd, int flags);

void read_blocks(int fd);
 
void read_headers(unsigned char h_buf, int flags);

#endif
