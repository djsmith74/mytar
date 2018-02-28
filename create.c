#include "create.h"
#include "direct.h"

int create_main(int argc, char *argv[], int fd, int flags) {
    int i;
    for (i = 3; i < argc; i++) {
        start_traverse(argv[i], fd, flags);
    }
/* struct stat stat_buf;
    stat("./", &stat_buf);
    char *header_test;
*/
   /* char *path_test;
    char *name_test;
    char *mode_test;
    char *uid_test;   
    char *gid_test; 
    char *size_test;
    char *mtime_test;
    char typeflag_test;
    char *magic_test;
    char *version_test;
    char *uname_test;
    char *gname_test;
    char *prefix_test;
    char *prefix_temp;
*/
    /* TESTS */
    /*path_test = "black/paper/mytar.txt";*/
    /*path_test = "/home/kmzhang/CPE357/Asgn4/mytar";*/
    /*prefix_temp = dirname(path_test);*/
    /*printf("name: %s\n", path_test);
    printf("mode: %o\n", stat_buf.st_mode);
    printf("uid: %o\n", stat_buf.st_uid);
    printf("gid: %o\n", stat_buf.st_gid);
    printf("size: %o\n", stat_buf.st_size);
    printf("mtime: %o\n", stat_buf.st_mtime);
    printf("typeflag: %d\n", S_ISDIR(stat_buf.st_mode));
    printf("magic: ustar\n");
    printf("version: 00\n");
    printf("uname: %s\n", getpwuid(stat_buf.st_uid)->pw_name);
    printf("gname: %s\n", getgrgid(stat_buf.st_gid)->gr_name);
    printf("prefix: %s\n", prefix_temp);
    printf("\n");
*/
    /*name_test = create_name(path_test);
    mode_test = create_mode(stat_buf);
    uid_test = create_uid(stat_buf);
    gid_test = create_gid(stat_buf);
    size_test = create_size(stat_buf, 0);
    mtime_test = create_mtime(stat_buf);
    typeflag_test = create_typeflag(2);
    magic_test = create_magic();
    version_test = create_version();
    uname_test = create_uname(stat_buf);
    gname_test = create_gname(stat_buf);
    prefix_test = create_prefix(path_test);

    printf("name_test: %s\n", name_test);
    printf("mode_test: %s\n", mode_test);
    printf("uid_test: %s\n", uid_test);
    printf("gid_test: %s\n", gid_test);
    printf("size_test: %s\n", size_test);
    printf("mtime_test: %s\n", mtime_test);
    printf("typeflag_test: %c\n", typeflag_test);
    printf("magic: %s\n", magic_test);
    printf("version: %s\n", version_test);
    printf("uname: %s\n", uname_test);
    printf("gname: %s\n", gname_test);
    printf("prefix: %s\n", prefix_test);
*/
    /* TESTING HEADER CREATION */
    /*header_test = calloc(BLOCK_SIZE, sizeof(char));
    header_test = create_header(path_test, 0);
   */ /*printf("header: %s\n", header_test);*/
    return 0;
}

/* Creates the archive entry with the header and file blocks */
void add_archive_entry(char *pathname, char *name, int fd,
                        int filetype, int flags) {
    struct stat sb;
    char* header;
    char* buffer;
    char* end_block1;
    char* end_block2;
    /*int block_nums;*/
    int i;
    /*int j;*/
    int fd_read;

    if (strlen(name) > NAME_LEN) {
        return;
    }

    buffer = calloc(BLOCK_SIZE, sizeof(char));
    fd_read = open(pathname, O_RDONLY); 
    header = create_header(pathname, name, filetype);
    end_block1 = calloc(BLOCK_SIZE, sizeof(char));
    end_block2 = calloc(BLOCK_SIZE, sizeof(char));

    memset(buffer, '\0', BLOCK_SIZE*sizeof(char));
    memset(end_block1, '\0', BLOCK_SIZE*sizeof(char));
    memset(end_block2, '\0', BLOCK_SIZE*sizeof(char));

    lstat(pathname, &sb);
    write(fd, header, BLOCK_SIZE);
    if (filetype == 0 && sb.st_size > 0) {
        while((i = read(fd_read, buffer, BLOCK_SIZE)) > 0) {
            write(fd, buffer, BLOCK_SIZE);
        }
    }
   
    /* Adding end blocks */
    write(fd, end_block1, BLOCK_SIZE);
    write(fd, end_block2, BLOCK_SIZE);
}

/* Fills a 512 byte block withheader information
 * Location for each field is defined in the header
 */
char* create_header ( char *pathname, char *name, int fileflag) {
    /* VARIABLES */
    struct stat sb;
    /*DIR *d;*/
    /*struct dirent entry;*/
    char *h_buffer;
    char *name_buff;
    char *mode_buff;
    char *uid_buff;
    char *gid_buff;
    char *size_buff;
    char *mtime_buff;
    char *chksum_buff;
    char *chksum_buff2;
    char typeflag_buff;
    char *linkname_buff;
    char *magic_buff;
    char *version_buff;
    char *uname_buff;
    char *gname_buff;
    char *devmajor_buff;
    char *devminor_buff;
    char *prefix_buff;
    int i;
    int chk_sum;
    
    /* INITIALIZATION */
    if ((h_buffer = calloc(BLOCK_SIZE, sizeof(char))) == NULL) {
        perror("bad calloc");
        exit(EXIT_FAILURE);
    }
    memset(h_buffer, '\0', BLOCK_SIZE*sizeof(char));
  
    if (lstat(pathname, &sb) == -1) {
        perror("bad stat");
        exit(EXIT_FAILURE);
    }

    name_buff = create_name(pathname);
    mode_buff = create_mode(sb);
    uid_buff = create_uid(sb);
    gid_buff = create_gid(sb);
    size_buff = create_size(sb, fileflag);
    mtime_buff = create_mtime(sb);
    chksum_buff = calloc(CHKSUM_LEN, sizeof(char));
    memset(chksum_buff, ' ', CHKSUM_LEN*sizeof(char));
    typeflag_buff = create_typeflag(fileflag);
    linkname_buff = create_linkname(pathname, fileflag); 
    magic_buff = create_magic();
    version_buff = create_version();
    uname_buff = create_uname(sb);
    gname_buff = create_gname(sb);
    devmajor_buff = calloc(DEVMAJOR_LEN, sizeof(char));
    devminor_buff = calloc(DEVMINOR_LEN, sizeof(char));
    memset(devmajor_buff, '\0', DEVMAJOR_LEN*sizeof(char)); 
    memset(devminor_buff, '\0', DEVMINOR_LEN*sizeof(char));
    prefix_buff = create_prefix(pathname);

    memcpy(h_buffer + NAME, name_buff, NAME_LEN*sizeof(char));
    memcpy(h_buffer + MODE, mode_buff, MODE_LEN*sizeof(char));
    memcpy(h_buffer + UID, uid_buff, UID_LEN*sizeof(char));
    memcpy(h_buffer + GID, gid_buff, GID_LEN*sizeof(char));
    memcpy(h_buffer + SIZE, size_buff, SIZE_LEN*sizeof(char));
    memcpy(h_buffer + MTIME, mtime_buff, MTIME_LEN*sizeof(char));
    memcpy(h_buffer + CHKSUM, chksum_buff, CHKSUM_LEN*sizeof(char));
    memcpy(h_buffer + TYPEFLAG, &typeflag_buff, TYPEFLAG_LEN*sizeof(char));
    memcpy(h_buffer + LINKNAME, linkname_buff, LINKNAME_LEN*sizeof(char));
    memcpy(h_buffer + MAGIC, magic_buff, MAGIC_LEN*sizeof(char));
    memcpy(h_buffer + VERSION, version_buff, VERSION_LEN*sizeof(char));
    memcpy(h_buffer + UNAME, uname_buff, UNAME_LEN*sizeof(char));
    memcpy(h_buffer + GNAME, gname_buff, GNAME_LEN*sizeof(char));
    memcpy(h_buffer + DEVMAJOR, devmajor_buff, DEVMAJOR_LEN*sizeof(char));
    memcpy(h_buffer + DEVMINOR, devminor_buff, DEVMINOR_LEN*sizeof(char));
    memcpy(h_buffer + PREFIX, prefix_buff, PREFIX_LEN*sizeof(char));

    /* CHKSUM */
    chk_sum = 0;
    for (i = 0; i < BLOCK_SIZE; i++) {
        chk_sum += (unsigned char)h_buffer[i];
    } 
    chk_sum = chk_sum - (CHKSUM_LEN*SPACE_ASCII);
    /*printf("chk_sum: %d\n", chk_sum);*/
    chksum_buff2 = create_chksum(chk_sum);
    /*printf("chksum_buff2: %s\n", chksum_buff2);*/
    memcpy(h_buffer + CHKSUM, chksum_buff2, CHKSUM_LEN*sizeof(char));
    
    return h_buffer;
} 

/* Create the chksum field */
char* create_chksum (int chk_sum) {
    int i;
    char *chksum_buffer;
    
    chksum_buffer = calloc(CHKSUM_LEN, sizeof(char));
    memset(chksum_buffer, '\0', CHKSUM_LEN*sizeof(char)); 
    memset(chksum_buffer, '0', (CHKSUM_LEN-1)*sizeof(char));
    i = CHKSUM_LEN-2;
   
    while (chk_sum != 0 && i > -1) {
        chksum_buffer[i] = (chk_sum % OCTAL_NUM) + ASCII_NUM_OFFSET;  
        /*printf("chksum_buffer: %c\n", chksum_buffer[i]);*/
        chk_sum = chk_sum / OCTAL_NUM;
        if (chk_sum != 0 && i == 0) {
            insert_special_int(chksum_buffer, CHKSUM_LEN, chk_sum);
        }
        i--;
    }
    return chksum_buffer;
}

/* Create the name field */
char* create_name ( const char *pathname ) {
    char *name_buffer;
    char *path_copy;
    char *base_name;
    int name_len;
    /*int rem_name_len;*/

    path_copy = strdup(pathname);
    name_buffer = calloc(NAME_LEN, sizeof(char));
    memset(name_buffer, '\0', NAME_LEN*sizeof(char)); 
    base_name = basename(path_copy);
    name_len = strlen(base_name);
    if (name_len <= NAME_LEN) {
        strncpy(name_buffer, base_name, name_len);
    }
    return name_buffer;
}

/* Create the mode field */
char* create_mode ( struct stat sb ) {
    char *mode_buffer;
    /*mode_buffer = make_octal(sb.st_mode);*/
    int i;
    mode_t mode_hold;

    mode_buffer = calloc(MODE_LEN, sizeof(char));    
    memset(mode_buffer, '\0', MODE_LEN*sizeof(char)); 
    memset(mode_buffer, '0', (MODE_LEN-1)*sizeof(char));
    mode_hold = sb.st_mode;  
    i = MODE_LEN-2;
   
    while (mode_hold != 0 && i > -1) {
        mode_buffer[i] = (mode_hold % OCTAL_NUM) + ASCII_NUM_OFFSET;  
        mode_hold = mode_hold / OCTAL_NUM;
        if (mode_hold != 0 && i == 0) {
            insert_special_int(mode_buffer, MODE_LEN, mode_hold);
        }
        i--;
    }
    return mode_buffer;
}

/* Create the uid field */
char* create_uid (struct stat sb) {
    char *uid_buffer;
    /*uid_buffer = make_octal(sb.st_uid);*/
    int i;
    uid_t uid_hold;
    uid_buffer = calloc(UID_LEN, sizeof(char));
    memset(uid_buffer, '\0', UID_LEN*sizeof(char)); 
    memset(uid_buffer, '0', (UID_LEN-1)*sizeof(char));   
    uid_hold = sb.st_uid;  
    i = UID_LEN-2;
   
    while (uid_hold != 0 && i > -1) {
        uid_buffer[i] = (uid_hold % OCTAL_NUM) + ASCII_NUM_OFFSET;  
        uid_hold = uid_hold / OCTAL_NUM;
        if (uid_hold != 0 && i == 0) {
            insert_special_int(uid_buffer, UID_LEN, uid_hold);
        }
        i--;
    }
    return uid_buffer;
}

/* Create the gid field */
char* create_gid (struct stat sb) {
    char *gid_buffer;
    /*gid_buffer = make_octal(sb.st_gid);*/
    int i;
    gid_t gid_hold;
    gid_buffer = calloc(GID_LEN, sizeof(char));
    memset(gid_buffer, '\0', GID_LEN*sizeof(char)); 
    memset(gid_buffer, '0', (GID_LEN-1)*sizeof(char));   
    gid_hold = sb.st_gid;  
    i = GID_LEN-2;
   
    while (gid_hold != 0 && i > -1) {
        gid_buffer[i] = (gid_hold % OCTAL_NUM) + ASCII_NUM_OFFSET;  
        gid_hold = gid_hold / OCTAL_NUM;
        if (gid_hold != 0 && i == 0) {
            insert_special_int(gid_buffer, GID_LEN, gid_hold);
        }
        i--;
    }
 
    return gid_buffer;
}

/* Create the size field */
char* create_size (struct stat sb, int filetype_flag) {
    char *size_buffer;
    /*size_buffer = make_octal(sb.st_size);*/
    int i;
    off_t size_hold;
    size_buffer = calloc(SIZE_LEN, sizeof(char)); 
    memset(size_buffer, '0', SIZE_LEN*sizeof(char));   
    
    if (filetype_flag == 1 || filetype_flag == 2) {
        return size_buffer;    
    }

    size_hold = sb.st_size;  
    i = SIZE_LEN-1;
   
    while (size_hold != 0 && i > -1) {
        size_buffer[i] = (size_hold % OCTAL_NUM) + ASCII_NUM_OFFSET;  
        size_hold = size_hold / OCTAL_NUM;
        if (size_hold != 0 && i == 0) {
            insert_special_int(size_buffer, SIZE_LEN, size_hold);
        }
        i--;
    }
    return size_buffer;
}

/* Create the mtime field */
char* create_mtime (struct stat sb) {
    char *mtime_buffer;
    /*gid_buffer = make_octal(sb.st_gid);*/
    int i;
    time_t mtime_hold;
    mtime_buffer = calloc(MTIME_LEN, sizeof(char)); 
    memset(mtime_buffer, '0', MTIME_LEN*sizeof(char));   
    mtime_hold = sb.st_mtime;  
    i = MTIME_LEN-1;
   
    while (mtime_hold != 0 && i > -1) {
        mtime_buffer[i] = (mtime_hold % OCTAL_NUM) + ASCII_NUM_OFFSET;  
        mtime_hold = mtime_hold / OCTAL_NUM;
        if (mtime_hold != 0 && i == 0) {
            insert_special_int(mtime_buffer, MTIME_LEN, mtime_hold);
        }
        i--;
    }
 
    return mtime_buffer;
}

/* Create the typeflag field */
char create_typeflag (int ftype_flag) {
    char typeflag_buffer;
    /*typeflag_buffer = calloc(TYPEFLAG_LEN, sizeof(char));*/
    if (ftype_flag == REG_FLAG) {
        typeflag_buffer = '0';
    }
    else if (ftype_flag == SYM_FLAG) {
        typeflag_buffer = '2'; 
    }
    else {
        typeflag_buffer = '5';
    }
    return typeflag_buffer;
}

/* Create the linkname */
char* create_linkname(char *pathname, int ftype_flag) {
    char *linkname_buffer;
    linkname_buffer = calloc(LINKNAME_LEN, sizeof(char));
    memset(linkname_buffer, '\0', LINKNAME_LEN*sizeof(char));
    if (ftype_flag == 1) {
        if (readlink(pathname, linkname_buffer, LINKNAME_LEN) == -1) {
            perror("bad readlink");
        }
    }
    return linkname_buffer;
}

/* Create the magic field */
char* create_magic () {
    char *magic_buffer = "ustar\0"; /* TO DO: CHANGE BACK TO '\0'" */
    return magic_buffer;
}

/* Create the version field */
char* create_version () {
    char *version_buffer = "00";
    return version_buffer;    
}

/* Create the uname field */
char* create_uname (struct stat sb) {
    char *uname_buffer;
    uname_buffer = calloc(UNAME_LEN, sizeof(char));
    memset(uname_buffer, '\0', UNAME_LEN*sizeof(char));
    strncpy(uname_buffer, getpwuid(sb.st_uid)->pw_name, UNAME_LEN);
    return uname_buffer;
}

/* Create the gname field */
char* create_gname (struct stat sb) {
    char *gname_buffer;
    gname_buffer = calloc(GNAME_LEN, sizeof(char));
    memset(gname_buffer, '\0', GNAME_LEN*sizeof(char));
    strncpy(gname_buffer, getgrgid(sb.st_gid)->gr_name, GNAME_LEN);
    return gname_buffer;
}

/* Don't need to create helper functions for devmajor and devminor */

/* Create the prefix field */
char* create_prefix ( char *pathname ) {
    char *prefix_buffer;
    char *path_copy;
    char *path_copy2;
    /*char *dir_name;*/
    char *base_name;
    int base_len;
    int path_len;
    int prefix_len;

    path_copy = strdup(pathname);
    path_copy2 = strdup(pathname);
    prefix_buffer = calloc(PREFIX_LEN, sizeof(char));
    /*memset(name_buffer, '\0', NAME_LEN*sizeof(char));*/
    base_name = basename(path_copy);
    base_len = strlen(base_name);
    path_len = strlen(path_copy);
    prefix_len = path_len - base_len - 1;
    strncpy(prefix_buffer, path_copy2, prefix_len);    

    /*dir_name = dirname(path_copy);*/
    /*prefix_len = strlen(dir_name);
    if (prefix_len <= PREFIX_LEN) {
        strncpy(prefix_buffer, dir_name, prefix_len);
    }
    else {
        perror("prefix too long");
        strncpy(prefix_buffer, dir_name, PREFIX_LEN);
    }*/
    return prefix_buffer; 
}

/* For interoperability with GNU tar. GNU seems to
 * set the high–order bit of the first byte, then
 * treat the rest of the field as a binary integer
 * in network byte order.
 * Insert the given integer into the given field
 * using this technique. Returns 0 on success, nonzero * otherwise
 * */
int insert_special_int(char *where, size_t size, int32_t val) { 
    int err=0;
    if(val<0||(size<sizeof(val)) ){
        /* if it’s negative, bit 31 is set and we can’t use the flag
         * if len is too small, we can’t write it. * done.
         */
        err++;
    } 
    else {
        /* game on....*/
        memset(where, 0, size);
        *(int32_t *)(where+size-sizeof(val)) = htonl(val);
        *where |= 0x80; /* set that high–order bit */
    }
    return err; 
}
