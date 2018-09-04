#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "system_comm.h"
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


void command_execute(char ** args,char * HOME,int end_position)
{
    if(strcmp(args[0],"exit")==0){
        free(args);
        exit(0);
    }
    else{
        if(strcmp(args[end_position-1],"&")==0)
            execute(args,HOME,1,end_position);
        else
            execute(args,HOME,0,end_position);
    }
}

#define TOKEN_BUFFSIZE 64
#define TOKEN_DELIMITER " \t\r\n\a"
void parse_line(char * line,char * HOME){

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
    command_execute(tokens,HOME,position);
    free(tokens);

}


int main(int argc,char * envp[]){

    char PATH[2048],NEW_PATH[2048];
    char *user = getenv("USER");
    char *hostname = getenv("HOSTNAME");
    struct utsname uname_pointer;
    uname(&uname_pointer);
    char * HOME = getenv("PWD");
    char * line;
    char ** flags;
    long long int i=0;
    while(1)
    {
        getcwd(PATH,sizeof(PATH));
        if(strstr(PATH,HOME)!=NULL){
            NEW_PATH[0]='~';
            long long int k=1;
            long long int LENGTH = strlen(HOME);
            for(i=LENGTH;i<(long long int)strlen(PATH);i++){
                NEW_PATH[k++]=PATH[i];
            }
            NEW_PATH[k]='\0';
        }
        else{ 
          for( i=0;i<(long long int)strlen(PATH);i++){
                NEW_PATH[i]=PATH[i];
            }
            NEW_PATH[i]='\0';  
        }
        printf("<%s@%s:%s>",user,uname_pointer.nodename,NEW_PATH);
        line = read_line();
        parse_line(line,HOME);
        free(line);
    }
    return 0;
}