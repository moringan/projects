/*
* Re-creation of the cp command
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // write()
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define COPYMODE 0644


void error(char *message, char *filename ) 
{
    fprintf(stderr, "%s ", message);
    perror(filename);
    exit(1);
}

/*
* Compare two strings, if the same return 1, if not return 0
*/
int str_same(char *str1, char *str2)
{
    
    if (strlen(str1) != strlen(str2))
        return 0;
    while (*str1 != '\0') {
        if (*str1 != *str2)
            return 0;
        str1++; str2++;
    }
    return 1;
}

int get_user_approval(FILE *tty_fp)
{
    int response;
    while ((response = getc(tty_fp)) != EOF) {
        if (response == 'n' || response == 'N')
            return 0;
        if (response == 'y' || response == 'Y')
            return 1;
    }
}

int main(int ac, char *av[]) 
{
    int src_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    int reads = 0;
    FILE *tty_fp;

    tty_fp = fopen("/dev/tty", "r");
    if ( (tty_fp = fopen("/dev/tty", "r")) == NULL) {
        printf("could not open /dev/tty\n");
        exit(1);
    }

    
    ssize_t bytes_read, bytes_written;

    if (ac != 3) 
    {
        fprintf(stderr, "usage: %s source destination\n", *av);
        exit(1);
    }

    if ( (ac == 3) && str_same(av[1], av[2]) )
    {
        fprintf(stderr, "source and desination cannot be the same\n");
        exit(1);
    }

    /* Check if file exists * */
    if ( access(av[2], F_OK) != -1)
    {
        printf("File exists, overwrite (y/n)? ");
        if (get_user_approval(tty_fp) == 0) 
            exit (0);
    }

    if ( (src_fd = open(av[1], O_RDONLY)) == -1 )
        error("Cannot open", av[1]);



    if ( ( dest_fd = creat(av[2], COPYMODE)) == -1 )
        error("Cannot create", av[2]);
    
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0)
    {
        if ( write(dest_fd, buffer, bytes_read) != bytes_read)
            error("Error writing", av[2]);    
        reads++;
    }

    if (bytes_read == -1)
        error("Error reading", av[1]);

    if (close(src_fd) == -1 || close(dest_fd) == -1)
	    error("Error closing files", "");

    printf("buffer size = %d\n", BUFFER_SIZE);
    printf("reads = %d\n", reads);


    return 0;
}

