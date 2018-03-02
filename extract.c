#include "extract.h"

int extract_main (int argc, char *argv[], int fd) {
    /* VARIABLES */
    struct stat sb_file;
    char *h_buf;
    unsigned char *h_bufp;
    unsigned char *path, *name;
    int num_blocks;
    long int file_size;

    /* INITIALIZATION */
    h_buf = calloc(BLOCK_SIZE, sizeof(char));

    /* check if file is empty */
    fstat(fd, sb_file);
    if (sb_file.st_size == 0) {
        return;
    }
     
    /* extract the gives paths from the archive file */
    if (argc > 3) {
        
    }
    /* extract all files from the archive */
    else {
        while (read(fd, h_buf, BLOCK_SIZE) > 0) {
            /* check for end of archive */ 
            if (strlen(h_buf) == 0) {
                 read(fd, h_buf, BLOCK_SIZE);
                 if (strlen(h_buf) == 0) {
                     return 0;
                 }
            }
            
            /* Get the pathname */
            h_bufp = h_buf + PREFIX;
            strcpy((char*)path, (char*)h_bufp);
            h_bufp = h_buf + NAME;
            strcpy((char*)name, (char*)h_bufp);
            strcat((char*)path,(char*)name);
            
            /* Get the type of the archive entry */
            h_bufp = h_buf + TYPEFLAG;

            /* Check if its a file */
            if (*h_buf == '0') {
                open(path, O_CREAT, 0777);
                num_blocks = 
                break;
            }
            /* Check if its a directory */
             else if (*h_buf = '2') {
                mkdir(path, 0777);
                break;
            }
            /* Check if it's a directory or symlink */
        }
    }
}

                                                                                                61,0-1        Bot

