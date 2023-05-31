#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
/*
* Program to read utmp and print results
* Using open() and read() instead of getutent()
*/

int main () 
{
    ssize_t bytes_read;
    int fd;
    struct utmp utmp_data;
    void show_info(struct utmp*);
    int utmp_len = sizeof(utmp_data);


    fd = open(UTMP_FILE, O_RDONLY);
    if (fd == -1) 
    {
        perror("failed to open utmp\n");
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(fd, &utmp_data, utmp_len)) == utmp_len)
    {
         show_info(&utmp_data);
 
    }
    close(fd);
        
}
void show_info(struct utmp *utmp_data)
{
    if (utmp_data->ut_type == USER_PROCESS)
            printf("%s\n", utmp_data->ut_user);
}