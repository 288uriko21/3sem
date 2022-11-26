// “pr1| pr2 |pr3|… |prN

#include <stdio.h>
int main(int argc, char *argv[])
{
    int fd[2], in, out, i;
    if (argc == 1)
        return 0;
    if (argc == 2)
        execlp(argv[1], argv[1], 0);

    /* argc>2 */
    pipe(fd);
    out = fd[1];
    if (fork() == 0)
    {// не закрываем fd[0]!!!
        dup2(out, 1);
        close(out);
        execlp(argv[1], argv[1], 0);
    }
    in = fd[0];
    for (i = 2; i < argc - 1; i++)
    {
        close(out);
        pipe(fd);
        out = fd[1];
        if (fork() == 0)
        {
            dup2(in, 0);
            close(in);
            dup2(out, 1);
            close(out);
            execlp(argv[i], argv[i], 0);
        }
        close(in);
        in = fd[0];
    }
    close(out);
    if (fork() == 0)
    {
        dup2(in, 0);
        close(in);
        execlp(argv[argc - 1], argv[argc - 1], 0);
    }
    close(in);
    for (i = 1; i < argc; i++)
        wait(NULL);
    return 0;
}