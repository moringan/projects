#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
* Recursively print the current working directory (like pwd)
* 
* Uses readdir() and chdir() to get inode number to find directory name
*
* one thing to remember is the inode for . and .. are the same in the root folder (/)
* so we can check for it, then traverse back through the functions, printing each folder name
*  
* by Mike Stapleton 5.19.23
*/

typedef enum { false, true } bool;

void print_path(ino_t ino_prev)
{
    ino_t ino_cur = 0;
    char dir_name[128]; 
    DIR *d;
    struct dirent * dir;
    bool found_cur_dir = false;
    bool found_ino_prev = false;

    if (ino_prev == 0)
    {
        found_ino_prev = true;
        dir_name[0] = '\0';
    }
    
    if ((d = opendir(".")) != NULL) 
    {
        while ((dir = readdir(d)) != NULL) 
        {
            if (!found_cur_dir)
                if (strcmp(dir->d_name, ".") == 0) 
                {
                    ino_cur = dir->d_ino;
                    found_cur_dir = true;
                }
            if (!found_ino_prev)
                if (dir->d_ino == ino_prev)
                {
                    strcpy(dir_name, dir->d_name); 
                    found_ino_prev = true;
                }
            if (found_cur_dir & found_ino_prev)     // we do this to not have to go through entire
                break;                              // file list if we don't have to
            
        }
    }
    closedir(d);

    if (!(ino_cur == ino_prev)) 
    {
        chdir("..");
        print_path(ino_cur);
    }
    
    // if we're in the root directory, dir_name is .. or . because the child inode matches current
    if ( (strcmp(dir_name, ".") != 0) && (strcmp(dir_name, "..") != 0) )
        printf("/%s", dir_name);
    
    
    return;
    

}

int main() {
    
    ino_t start_ino = 0;

    print_path(start_ino);
    printf("\n");

    return 0;
}