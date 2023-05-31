#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>

int main(int ac, char *av[]) 
{
    char *filename = av[1];
    struct dirent *dir; 
    struct stat statbuf;
    struct passwd *passw;
    struct group *grp;
    
    //if (ac < 2)
      //  exit(1);
    DIR *dirs =  opendir("/usr");
    if ((dir = readdir(dirs)) != NULL)
        printf("%s\n", dir->d_name);
    while ((dir = readdir(dirs)) != NULL)
        printf("%s ", dir->d_name);
    
    closedir(dirs);
    printf("\n");
    if(stat(filename, &statbuf) != -1)
    {
        if ( (statbuf.st_mode & 0170000) == 0040000 )
            printf("%s is a directory\n",filename);
        
        if ( (statbuf.st_mode & 0170000) == 0100000 )
            printf("%s is a regular file\n", filename);
        
        if ( ! (statbuf.st_mode & S_IXUSR)) {
            
            printf("%s -- User does not have execute permission\n", filename);
            printf("%b\n", (statbuf.st_mode & S_IRUSR));
        }
        
        if ( statbuf.st_mode & S_IRUSR )
            printf("%s User has read permission\n", filename);
        printf("sizeof st_mode: %d\n", (int)sizeof(mode_t));
        if (S_ISREG(statbuf.st_mode))
            printf("is a reg file\n");
        if ( (passw = getpwuid(statbuf.st_uid)) != NULL )
            printf("The user's name is %s\n", passw->pw_name);
        if ( (grp = getgrgid(statbuf.st_gid)) != NULL )
            printf("The user's group is %s\n", grp->gr_name);
    }
    return 0;
}