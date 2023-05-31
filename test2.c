/*	prompting shell version 1
 *		Prompts for the command and its arguments.
 *		Builds the argument vector for the call to execvp.
 *		Uses execvp(), and never returns.
 */

#include	<stdio.h>
#include	<signal.h>
#include	<string.h>
#include    <unistd.h>
#include    <sys/wait.h>
#include    <ctype.h>


#define	MAXARGS		20				/* cmdline args	*/
#define	ARGLEN		100				/* token length	*/
#define EXIT_STRING "quit"

int main()
{

    char	*arglist[MAXARGS+1];		/* an array of ptrs	*/
	char	argbuf[ARGLEN];			/* read stuff here	*/
	char	*makestring();			/* malloc etc		*/
    int     word_count = 0;
    
    struct sigaction sa_ignore;
    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    if (sigaction(SIGINT, &sa_ignore, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    while (1)
    {					
        printf("command: ");
        if ( fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n' )
        {
            /* remove the newlinecharacter at the end of the string */
            argbuf[strcspn(argbuf, "\n")] = '\0';

            /* checkif user want to quit the shell */
            if (strcmp(argbuf, EXIT_STRING) == 0)
                break;

            /* tokenize the string and put into an array */
            char *token = strtok(argbuf, " ");
            while ((token != NULL) && (word_count < MAXARGS) ) {
                arglist[word_count] = malloc(strlen(token) + 1); // Allocate memory for the word
                strcpy(arglist[word_count], token); // Copy the token into the allocated memory
                word_count++;
                token = strtok(NULL, " ");
            }
            arglist[word_count]=NULL;	/* close list	*/
            word_count = 0;  /* reset */
            execute(arglist);
            
        }

    }
	return 0;
}


void execute( char *arglist[] )
/*
 *	use execvp to do it
 */
{
    int child_pid;
    char c;

	//int wait_return_pid;
    int child_return_status;
    child_pid = fork();
    switch(child_pid)
    {
        case -1:
            perror("fork error");
            exit(1);
        case  0:
            execvp(arglist[0], arglist);
            //perror("execvp failed");
            perror(arglist[0]);
            exit(1);
        default:
            while(wait(&child_return_status) != child_pid)
                ;
            if (WIFEXITED(child_return_status)) 
                printf("Child exited with status %d\n", WEXITSTATUS(child_return_status));
    }
}


char * makestring( char *buf )
/*
 * trim off newline and create storage for the string
 */
{
	char	*cp; 
	buf[strlen(buf)-1] = '\0';		/* trim newline	*/
	cp = malloc( strlen(buf)+1 );		/* get memory	*/
	if ( cp == NULL ){			/* or die	*/
		fprintf(stderr,"no memory\n");
		exit(1);
	}
	strcpy(cp, buf);		/* copy chars	*/
	return cp;			/* return ptr	*/
}