#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

void command_cd(char ** args,char * HOME)
{
    int ret_val;    
    if(args[1] == NULL){
       ret_val = chdir(HOME);
    } 
    else if(strstr(args[1],"~") != NULL){
        char * token = strtok(args[1],"~");
        strcat(HOME,token);
        ret_val = chdir(HOME);
        if(ret_val < 0){
           printf("No such directory exists.\n");
        }
    }
    else{
        ret_val=chdir(args[1]);
        if(ret_val < 0){
            printf("No such directory exists.\n");
        }
        
    }
}


void command_pwd(char ** args)
{
    if(args[1] != NULL){
        printf("bash: pwd: %s :invalid option",args[1]);
    }
    else
    {
        char path[2048];
        getcwd(path,2048);
        printf("%s\n",path);
    }
}


void command_echo(char ** args,int end_position)
{
    if(end_position<=1) {
        printf("\n");
  }
  for (int i = 1; i < end_position; i++)
  {
  	if(args[i][0]=='$')
  	{
  		const char* s = getenv(args[i]+1);
  		if(s!=NULL) printf("%s ",s);
  	}
  	else
  	{
	    int j;
	    for(j=0;args[i][j]!='\0';j++)
	    {
	      if(args[i][j]!='"') printf("%c",args[i][j]);
	    }

        printf(" ");
	}
  }
    printf("\n");
}


void command_ls(char ** args)
{
    char path[2048];
    struct dirent *descr;
    getcwd(path, 2048);
    DIR * dir_desc = opendir(path);
    if( dir_desc == NULL){
        perror("Cannot find directory");
        exit(-1);
    }
    if(strcmp(args[1],"-l")==0){
        while(descr = readdir(dir_desc)){
            if(strcmp(descr->d_name,".") != 0 && strcmp(descr->d_name,"..")!=0 ){
            struct stat fileStat;
            struct group * grp;
            struct passwd * pwd;
            stat(descr->d_name,&fileStat);
            struct tm * time_stamp = gmtime(&(fileStat.st_mtime));
            grp = getgrgid(fileStat.st_gid);
            pwd = getpwuid(fileStat.st_uid);
            printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf("\t%lu",fileStat.st_nlink);
            printf("\t%s",pwd->pw_name);
            printf("\t%s",grp->gr_name);
            printf("\t%lu",fileStat.st_size);
            printf("\t%s",descr->d_name);
            printf("\n");
            }
        }

    }
    else if(strcmp(args[1],"-a")==0){
          while(descr = readdir(dir_desc) )
            printf("%s\n",descr->d_name);
    }
    else if(strcmp(args[1],"-la")==0 || strcmp(args[1],"-al")==0){
            while(descr = readdir(dir_desc)){
            struct stat fileStat;
            struct group * grp;
            struct passwd * pwd;
            stat(descr->d_name,&fileStat);
            struct tm * time_stamp = gmtime(&(fileStat.st_mtime));
            grp = getgrgid(fileStat.st_gid);
            pwd = getpwuid(fileStat.st_uid);
            printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf("\t%lu",fileStat.st_nlink);
            printf("\t%s",pwd->pw_name);
            printf("\t%s",grp->gr_name);
            printf("\t%lu",fileStat.st_size);
            printf("\t%s",descr->d_name);
            printf("\n");
        }
    }
    else{
        while(descr = readdir(dir_desc) )
        {
            if(strcmp(descr->d_name,".") != 0 && strcmp(descr->d_name,"..")!=0 )
                printf("%s\n",descr->d_name);
        }
    }
    closedir(dir_desc);
}