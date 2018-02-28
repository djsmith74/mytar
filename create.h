#ifndef CREATE_H
#define CREATE_H

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <libgen.h>
#include <fcntl.h>

/* HEADER FIELD OFFSETS */
#define NAME 0
#define MODE 100
#define UID 108
#define GID 116
#define SIZE 124
#define MTIME 136
#define CHKSUM 148
#define TYPEFLAG 156
#define LINKNAME 157
#define MAGIC 257
#define VERSION 263
#define UNAME 265
#define GNAME 297
#define DEVMAJOR 329
#define DEVMINOR 337
#define PREFIX 345

/* HEADER FIELD LENGTHS */
#define NAME_LEN 100
#define MODE_LEN 8
#define UID_LEN 8
#define GID_LEN 8
#define SIZE_LEN 12
#define MTIME_LEN 12
#define CHKSUM_LEN 8
#define TYPEFLAG_LEN 1
#define LINKNAME_LEN 100
#define MAGIC_LEN 6
#define VERSION_LEN 2
#define UNAME_LEN 32
#define GNAME_LEN 32
#define DEVMAJOR_LEN 8
#define DEVMINOR_LEN 8
#define PREFIX_LEN 155

/* HEADER BLOCK SIZE */
#define BLOCK_SIZE 512

/* FLAGS */
#define REG_FLAG 0
#define SYM_FLAG 1
#define DIR_FLAG 2

/* OTHER */
#define ASCII_NUM_OFFSET 48
#define OCTAL_NUM 8
#define SPACE_ASCII 32

/* FUNCTIONS */
int create_main(int argc, char *argv[], int fd, int flags);
void add_archive_entry(char *pathname, int fd, int flags, int filetype);
char* create_header ( char *pathname, int fileflag );
char* create_chksum (int chk_sum );
char* create_name ( char *pathname );
char* create_mode (struct stat sb);
char* create_uid (struct stat sb);
char* create_gid (struct stat sb);
char* create_size (struct stat sb, int filetype_flag);
char* create_chksum ();
char* create_mtime (struct stat sb);
char create_typeflag (int ftype_flag);
char* create_linkname ( char *pathname, int ftype_flag);
char* create_magic ();
char* create_version ();
char* create_uname (struct stat sb);
char* create_gname (struct stat sb);
char* create_prefix ( char *pathname );

#endif
