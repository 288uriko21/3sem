#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>


/*выводит данные о сыне: как завершился/убили/остановили или мб если егоне удалось породить*/
int main()
{
    pid_t child_pid, pid;
    int status;
    switch (child_pid = fork())
    {
    case (pid_t)-1:
        perror("fork");
        _exit(1);
    case (pid_t)0:
        printf("Son created\n");
        sleep(2);
        _exit(15);
    default:
        printf(" Parent after fork\n");
        /* kill(child_pid, SIGSTOP);*/
        /* kill(child_pid, SIGSTERM);*/
        pid = waitpid(child_pid, &status, WUNTRACED);
    }
    if (WIFEXITED(status))
        fprintf(stderr, "%d exits: %d\n", pid, WEXITSTATUS(status));
    else if (WIFSTOPPED(status))
        fprintf(stderr, "%d stopped by: %d\n", pid, WSTOPSIG(status));
    else if (WIFSIGNALED(status))
        fprintf(stderr, "%d killed by: %d\n", pid, WTERMSIG(status));
    else
        perror("waitpid");
    _exit(0);
}
