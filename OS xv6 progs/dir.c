#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
int main()
{
    DIR *mydir;
    struct passwd *pwd;
    struct group *grp;
    struct dirent *myfile;
    struct stat mystat; 
    char d[20]="";
    char buf[4096]="";
    printf("Enter the directory you want to show listing for: or enter(./) for the current directory...\n");
    fgets(d, 100, stdin);
    //strtok(d,"\0");
    strtok(d,"\n");
    if((mydir = opendir(d))!=NULL)
    {
    while((myfile = readdir(mydir)) != NULL)
    {
         char fullpath[30]="";
         snprintf(fullpath, sizeof(fullpath), "%s/%s", d, myfile->d_name);
         sprintf(buf, "%s", fullpath);
         stat(buf, &mystat);
         char *p = ctime(&mystat.st_ctime);
         p+=4;
         char f[11]="";
         int len = strlen(p)-9;
         strcat(f,(S_ISDIR(mystat.st_mode) ? "d" : "-"));
         strcat(f,(mystat.st_mode & S_IRUSR) ? "r" : "-");
         strcat(f,(mystat.st_mode & S_IWUSR) ? "w" : "-");
         strcat(f,(mystat.st_mode & S_IXUSR) ? "x" : "-");
         strcat(f,(mystat.st_mode & S_IRGRP) ? "r" : "-");
         strcat(f,(mystat.st_mode & S_IWGRP) ? "w" : "-");
         strcat(f,(mystat.st_mode & S_IXGRP) ? "x" : "-");
         strcat(f,(mystat.st_mode & S_IROTH) ? "r" : "-");
         strcat(f,(mystat.st_mode & S_IWOTH) ? "w" : "-");
         strcat(f,(mystat.st_mode & S_IXOTH) ? "x" : "-");
         if((pwd = getpwuid(mystat.st_uid))!=NULL)
         {
            if((grp = getgrgid(mystat.st_gid))!=NULL)
            { 
                printf("%.2lu   %.12s   %-8.8s   %-16.16s   %.6zu   %-4.*s   %s\n",mystat.st_blocks, f, pwd->pw_name, grp->gr_name, mystat.st_size, len, p, myfile->d_name);
            }
            else
                printf("%.2lu   %.12s   %-8.8s   %.3d   %.6zu   %-4.*s   %s\n",mystat.st_blocks, f, pwd->pw_name, mystat.st_gid, mystat.st_size, len, p, myfile->d_name);
         }
         else
         {
             if((grp = getgrgid(mystat.st_gid))!=NULL)
            {
                printf("%.2lu   %.12s   %.3d   %-16.16s   %.6zu   %-4.*s   %s\n",mystat.st_blocks, f, mystat.st_uid, grp->gr_name, mystat.st_size, len, p, myfile->d_name);
            }
            else
                printf("%.2lu   %.12s   %.3d   %.3d   %.6zu   %-4.*s   %s\n",mystat.st_blocks, f, mystat.st_uid, mystat.st_gid, mystat.st_size, len, p, myfile->d_name);
         }
    }
    closedir(mydir);
    }
    else
        printf("Directory not found");
}