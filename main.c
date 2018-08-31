#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/utsname.h>

int main(int argc,char * envp[]){

    while(1)
    {
        int n;
        char *user = getenv("USER");
        char *hostname = getenv("HOSTNAME");
        struct utsname uname_pointer;
        uname(&uname_pointer); 
        printf("<%s@%s:~>",user,uname_pointer.nodename);
        scanf("%d",&n);
    }
    return 0;
}