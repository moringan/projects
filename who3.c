/**
 * who3.c Read /etc/utmp, display the list of /etc/utmp.
 * 
 * Uses library utmplib to get each utmp record
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include "utmplib.h"

/* # define SHOWHOST */
void showtime(long);
void show_info(struct utmp *);

int main() {
  struct utmp *utcurrec;
  int utmpfd;

  if ((utmpfd = utmp_open(UTMP_FILE)) == -1) {
    perror(UTMP_FILE);
    exit(1);
  }

  while((utcurrec = utmp_next()) != ((struct utmp *) NULL))
    show_info(utcurrec);
  
  utmp_close();
  return 0;
}

void show_info(struct utmp *utcurrec) {
  //if (utcurrec->ut_type != USER_PROCESS)
	//return;
  printf("%-8.8s", utcurrec->ut_name);
  printf(" ");
  printf("%-8.8s", utcurrec->ut_line);
  printf(" ");
  showtime(utcurrec->ut_time);
  #ifdef SHOWHOST
  if(utcurrec->ut_host[0] != '/0')
	printf(" (%s)", utcurrec->ut_host);
  #endif
  printf("\n");
}

void showtime(long timeval) {
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp + 4);
}
