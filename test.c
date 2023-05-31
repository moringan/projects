#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <utmp.h>
#include <fcntl.h>
#include <dirent.h>
#include <termios.h>
#include <ctype.h>

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

int main() {
    char string1[] = "asdf";
    char string2[] = "asds";
    char buffer[BUFSIZ];
    struct dirent dir_entry;
    DIR *the_dir;
    FILE *the_file;
    char filename = "cp.c";
    
    //struct termios attribs;
    //tcgetattr(fd, &attribs);
    

    //fd = open("/dev/pts/1", O_RDWR);
    char buf[] = "Hello\n";
    int fd = 1;
    // A FILE is a buffer around file descriptors
    // stdout is buffered for example
    //write(fd, buf, strlen(buf));

    int i = 5500004400;
//    printf("%d\n", !i);
    char c;

    int return_from_fork, mypid;

    mypid = getpid();
    printf("Before fork my pid is %d\n", mypid);
    //sleep(1);
    fork();
    fork();
    fork();
    printf("My pid is %d\n", getpid());
    //fflush(stdout);


    /*while ( (c=getchar()) != EOF)
    {
        if (c == 'z')
            c = 'a';
        else if (islower(c))
            c++;
        putchar(c);
    }*/
    
    //int c, n = 0;
    //while ((c = getchar()) != 'Q')
    //    printf("char %3d is %c code %d\n", n++, c, c);
    //while(fgets(buffer, BUFSIZ, stdin) != NULL)
    //    write(fd, buffer, strlen(buffer));


    //if (chdir("..") == -1)
    //    perror("chdir: ");
    


/*
    if ((the_file = fopen(filename, O_RDONLY)) == NULL)
        perror("filename");

    fclose(the_file);
     

    //while (fgets(buffer, 32, stdin) !=NULL)
      //  printf("%s", buffer);

    if(str_same(string1, string2))
        printf("strings same %s %s", string1, string2);
    else
        printf("strings different %s %s", string1, string2);
    printf("UTMP_FILE: %s\n", UTMP_FILE);
  */
  return 0;
}