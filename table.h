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
#define SIZE_OFFSET 124
#define TIME_OFFSET 136
#define CHKS_OFFSET 148
#define TYPE_OFFSET 156
#define OWNR_OFFSET 265
#define GRUP_OFFSET 297
#define PREF_OFFSET 345

int table_main(char *argv[], int num, int fd, int flags);

int read_headers(char *argv[], int num, int fd, int flags);

void read_blocks(int fd, long int size);
 
void print_header(unsigned char *h_buf, unsigned char *path,
                  int flags, int type);


void print_perms(char *oct);

void print_time(long int time);

#endif
