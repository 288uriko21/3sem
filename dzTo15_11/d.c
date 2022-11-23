/// cmd1; cmd2; cmd3; ....

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int status;
    //printf("%d", argc);
    for (int i = 1; i < argc; ++i)
        if (fork() > 0)
            wait(&status);
        else
        {
            execlp(argv[i], argv[i], (char *)0);
            printf("Faild exec\n");
            exit(0);
        }
    return 0;
}