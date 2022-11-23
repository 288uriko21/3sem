#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

// сын записывает инфу, отец читает и выводит
int main()
{
   pid_t child_pid;
   int fifo[2], status;
   char buf[80];
   if (pipe(fifo) == -1)
      perror("pipe"), _exit(1);
   switch (child_pid = fork())
   {
   case -1:
      perror("fork");
      _exit(2);
   case 0:
      close(fifo[0]);
      sprintf(buf, "Child %d executed\n", getpid());
      write(fifo[1], buf, strlen(buf));
      close(fifo[1]);
      _exit(0);
   }
   /*parent */
   close(fifo[1]);
   while (read(fifo[0], buf, 1))
      putchar(buf[0]);
   putchar('\n');
   close(fifo[0]);
   if (waitpid(child_pid, &status, 0) == child_pid && WIFEXITED(status))
      return WEXITSTATUS(status);
   _exit(0);
}
