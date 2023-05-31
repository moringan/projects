#include <stdio.h>
#include <ncurses.h>
#include <signal.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

int time_interval = 1;

int screen_rows, screen_cols;
int x_pos = 0;
int dir = 1;

void set_alarm_interval(int n_msecs)
{
    struct itimerval new_timeset;
    long    n_sec, n_usecs;

    n_sec = n_msecs / 1000 ;
    n_usecs = ( n_msecs % 1000 ) * 1000L ;

    new_timeset.it_interval.tv_sec  = n_sec;        /* set reload  */
    new_timeset.it_interval.tv_usec = n_usecs;      /* new ticker value */
    new_timeset.it_value.tv_sec     = n_sec  ;      /* store this   */
    new_timeset.it_value.tv_usec    = n_usecs ;     /* and this     */

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void move_ball()
{
    clear();
    mvprintw(20, x_pos, "o");
    refresh();
    x_pos += dir;
    if((dir == 1) && (x_pos >= (screen_cols - 1)))
        dir = -1;
    else if((dir == -1) && (x_pos <= 0))
        dir = 1;

}

int main () 
{
    char c;

    /* Remove Blocking */
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flags |= O_ASYNC);
    
    initscr();
	//noecho();
	//curs_set(FALSE);
	getmaxyx(stdscr, screen_rows, screen_cols);
	//cbreak();	
	//nodelay(stdscr, TRUE);
    signal(SIGALRM, move_ball);
    set_alarm_interval(time_interval);   
    while (c =getch() != 'q');
    endwin();

}