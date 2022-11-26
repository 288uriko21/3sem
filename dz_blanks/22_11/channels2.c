// “pr1| pr2 |pr3|… |prN

#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int fd[2], in, out, next_in, i;
    if (argc == 1)
        return 0;
    if (argc == 2)
    {
        execlp(argv[1], argv[1], 0);
        exit(-1);
    }

    /* argc>2 */
    pipe(fd);
    out = fd[1];
    next_in = fd[0];

    if (fork() == 0)
    {
        close(next_in);
        dup2(out, 1);
        close(out);
        execlp(argv[1], argv[1], 0);
        exit(-1);
    }
    in = next_in;
    for (i = 2; i < argc - 1; i++)
    {
        close(out);
        pipe(fd);
        out = fd[1];
        next_in = fd[0];
        if (fork() == 0)
        {
            close(next_in);
            dup2(in, 0);
            close(in);
            dup2(out, 1);
            close(out);
            execlp(argv[i], argv[i], 0);
            exit(-1);
        }
        close(in);
        in = next_in;
    }
    close(out);
    if (fork() == 0)
    {
        dup2(in, 0);
        close(in);
        execlp(argv[argc - 1], argv[argc - 1], 0);
        exit(-1);
    }
    close(in);
    for (i = 1; i < argc; i++)
        wait(NULL);
    return 0;
}