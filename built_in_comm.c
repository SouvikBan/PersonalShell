#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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