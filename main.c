#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "built_in_comm.h"
#include <sys/utsname.h>


#define READLINE_BUFFSIZE 1024 
char *read_line()
{
    int buffersize = READLINE_BUFFSIZE;
    int position=0;
    char * buffer = malloc(sizeof(char) * buffersize);
    int ch;
    while(1)
    {
        ch = getchar();
        if( ch == EOF || ch == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else{
            buffer[position++] = ch;
        }

        if(position >= buffersize){
            buffersize += READLINE_BUFFSIZE;
            buffer = realloc(buffer, buffersize);

        }
    }

}


#define TOKEN_BUFFSIZE 64
#define TOKEN_DELIMITER " \t\r\n\a"
char ** parse_line(char * line){

    int buffersize = TOKEN_BUFFSIZE , position = 0;

    char **tokens = malloc(buffersize * sizeof(char *));
    char *token;

    token = strtok(line, TOKEN_DELIMITER);
    while(token != NULL){
        tokens[position]=token;
        position ++;

        if(position >= buffersize){
            buffersize += TOKEN_BUFFSIZE;
            tokens = realloc(tokens, buffersize * sizeof(char *)); 
        }

        token = strtok(NULL, TOKEN_DELIMITER); 
    }
    tokens[position] = NULL;
    return tokens;

}



void command_execute(char ** args,char * envp[],char * HOME)
{
    if( strcmp(args[0],"pwd")==0 ){
        command_pwd(args);
    }
    else if(strcmp(args[0],"cd")==0){
        command_cd(args,HOME);
    }
    else if(strcmp(args[0],"echo")==0){
        command_echo(args);
    }
}

int main(int argc,char * envp[]){

    while(1)
    {
        char * line;
        char PATH[2048];
        char ** flags;
        char *user = getenv("USER");
        char *hostname = getenv("HOSTNAME");
        struct utsname uname_pointer;
        uname(&uname_pointer); 
        char * HOME = getenv("PWD");
        printf("<%s@%s:%s>",user,uname_pointer.nodename,PATH);
        line = read_line();
        flags = parse_line(line);
        command_execute(flags,envp,HOME);
        free(line);
        free(flags);
    }
    return 0;
}