int execute(char **,char *,int,int);

typedef struct 
  {
    int id;
    char name[100];
  } Proc;
extern int proc_count;

extern Proc proc_arr[100];