#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

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


int command_echo(char ** args)
{
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
    if(args[1]==NULL){
        while(descr = readdir(dir_desc) )
        {
            if(strcmp(descr->d_name,".") != 0 && strcmp(descr->d_name,"..")!=0 )
                printf("%s\n",descr->d_name);
        }
    }
    else if(strcmp(args[1],"-l")==0){
        while(descr = readdir(dir_desc))
        {
            int filedesc = open(descr->d_name,O_WRONLY); 
            struct stat fileStat;
            stat(filedesc,&fileStat);
            

        }
    }
    else if(strcmp(args[1],"-a")==0){
          while(descr = readdir(dir_desc) )
            printf("%s\n",descr->d_name);
    }
    else if(strcmp(args[1],"-la")==0 || strcmp(args[1],"-al")==0){
       
    }
    closedir(dir_desc);
}