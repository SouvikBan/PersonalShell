#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include "built_in_comm.h"
#include "pinfo.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int execute(char **args,char *HOME,int background,int end_position)
{
  typedef struct 
  {
    int id;
    char name[100];
  } Proc;

  pid_t pid, wpid;
  int status;
  extern int proc_count;

  extern Proc proc_arr[100];

  pid = fork();
  if (pid == 0) {
    if( strcmp(args[0],"pwd")==0 ){
        command_pwd(args);
    }
    else if(strcmp(args[0],"cd")==0){
        command_cd(args,HOME);
    }
    else if(strcmp(args[0],"echo")==0){
        command_echo(args,end_position);
    }
    else if(strcmp(args[0],"ls")==0){
        command_ls(args);
    }
    else if(strcmp(args[0],"pinfo")==0){
      pinfo(args,HOME,strlen(HOME));
    }
    else{
      if (execvp(args[0], args) == -1) {
        perror("bash");
        }
        exit(EXIT_FAILURE);
      }
    } 
    else if (pid < 0) {
    perror("bash");
  } else if(background==0){
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
    else{
      //waitpid(-1,&status,WNOHANG);
      proc_count++; 
      proc_arr[proc_count].id = (int) pid;
      strcpy(proc_arr[proc_count].name,args[0]);
    }
    return 0;
}

