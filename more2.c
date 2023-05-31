#include <stdio.h>
#include <stdlib.h>
#define LINELEN 512
#define PAGELEN 24

int ask_to_continue(FILE * tty_fp)
{
    int response;
    printf("\033[7m more? \033[m");
    while ((response = getc(tty_fp)) != EOF) {
        if (response == 'q' || response == 'Q')
            return 0;
        if (response == ' ')
            return PAGELEN;
        if (response == '\n')
            return 1;
    }
}

void show_page(FILE *fp)
 /* 
 *  Take a file pointer, to either a file
 *  or a file stream (stdin) and 
 *  print one page at a time
 */
{
    char string[LINELEN];
    int lines = 0;
    int reply; 
    
    FILE *tty_fp;
    tty_fp = fopen("/dev/tty", "r");
    if ( (tty_fp = fopen("/dev/tty", "r")) == NULL) {
        printf("could not open /dev/tty\n");
        exit(1);
    }

    while (fgets(string, LINELEN, fp)) 
    {
        if (lines == PAGELEN) {
            lines = 0;
            reply = ask_to_continue(tty_fp);
            if (reply == 0) 
                break;
            lines -= reply;                
        }

        if(fputs(string, stdout) == EOF)
            exit(1);
        lines++;
    }
    fclose(tty_fp);

}
int main(int ac, char * av[]) 
{
    
    FILE *fp;  /* create a variable for a type FILE*/
    char string[LINELEN]; /* the current line*/
    
    if (ac == 1)
        show_page(stdin);
        
    else
    {   
        if ((fp = fopen(*++av, "r")) != NULL) 
        {
            show_page(fp);
        }
        else
            exit(1);
        fclose(fp);

    }
    
    
    exit(0);

}
    