#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define NAME_OFFSET 0
#define MODE_OFFSET 100
#define OWNR_OFFSET 108
#define GRUP_OFFSET 116
#define SIZE_OFFSET 124
#define TIME_OFFSET 136
#define TYPE_OFFSET 156
#define PREF_OFFSET 345

int table_main(char *argv[], int num, int fd, int flags);

int read_headers(char *argv[], int num, int fd, int flags);

void read_blocks(int fd);
 
void print_header(unsigned char *h_buf, unsigned char *path, int flags, int type);

void get_perms(unsigned char *h_buf, char permissions[8]);

char *create_time(int time);

#endif
