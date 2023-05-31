#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
#include <sys/types.h>

/*
* Title:  
*
* Get utmp  from kernel buffer to user process buffer
* 
* Description:
* 
* Use read to get utmp records from kernal buffer,
* store in user buffer utmp_buf.
* 
* If last utmp record from utmp_buf has been
* read, get more records from kernel buffer.
* Reading groups of records from kernel at a time
* instead of one at a time is more efficient
* 
* */

/* Number of utmp records to read into the buffer */
#define NUM_RECORDS 4

/* The size in bytes of one utmp record */
#define UTMP_SIZE (sizeof(struct utmp))

static int      utmp_fd = -1;
static char     utmp_buf[NUM_RECORDS * UTMP_SIZE];
static int      current_record; // the current record in the buffer, if current
                                // record == num_read -1, then you are at the last record
static int      num_read;  // number of utmp records read into the buffer (not always same as NUM_RECORDS
static int      kernel_reads = 0;

int get_more_utmp() {
    num_read = read(utmp_fd, utmp_buf, NUM_RECORDS * UTMP_SIZE) / UTMP_SIZE;
    if (num_read == -1) {
        perror("Error reading utmp");
        exit(1);
    }
    
    if (num_read == 0) {
        return 0;
    }
    kernel_reads++;
    current_record = 0;
}

struct utmp *utmp_next() {
    struct utmp *utmp_rec;
    
    if (utmp_fd == -1)  // an error, perhaps if calling the function without opening utmp first?
        return (struct utmp *)NULL;
        
    if (current_record == num_read) // out of records in our buffer, go get more
        if (get_more_utmp() == 0) {
            //printf("%d kernel reads\n", kernel_reads);
            return (struct utmp *)NULL;
        }
    utmp_rec = (struct utmp *)&utmp_buf[current_record * UTMP_SIZE];
    
    //Print the current record number in the buffer about to be printed.
    //printf("current record: %d\n", current_record);
    current_record++;

    
    return utmp_rec;
   
}

int utmp_open(char *filename) {
    if ( (utmp_fd = open(filename, O_RDONLY)) == -1 ) {
        perror("Can't open file");
        return -1;
    }
    current_record = 0;
    num_read = 0;
    return utmp_fd;
}

void utmp_close()
{
    if ( close(utmp_fd) == -1 ) {
        perror("Can't close file");
    }
    printf("Number of kernel reads: %d\n", kernel_reads);
}