#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int System (const char* cmd) /* "system"-function emulation:  int system (const char* cmd)  */
{
   pid_t  pid;
   int    status;
   switch(pid=fork())
   {
      case (pid_t) -1:  return -1;  /* fork failed */
      case (pid_t)  0:  execl("/bin/sh", "sh", "-c", cmd, 0);
                        perror("execl");
                        exit(errno);
      default: ;/* nothing */  
   }
    if (waitpid(pid,&status,0)==pid && WIFEXITED(status))
       return(WEXITSTATUS(status));
    return -1;
}

int main ()
{
   int    rc=0;
   char   buf[256];
   do
  { 
       printf("sh> "); fflush(stdout);
       if (!gets(buf)) break;
       rc = System(buf);
  } while(!rc);
   return (rc);
}

