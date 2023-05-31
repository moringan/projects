#ifndef UTMPLIB_H
#define UTMPLIB_H

int utmp_open(char *);
void utmp_close();
struct utmp *utmp_next();

#endif
