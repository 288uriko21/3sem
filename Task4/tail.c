#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define N 10

int getmode(char *str, long *count)
{
    *count = 10;

    if (str[0] == '-' || str[0] == '+')
    {
        char *nptr = str + 1, **endptr;
        *count = strtol(nptr, endptr, 10);
        if (str[0] == '-')
            return 1;
        else
            return 2;
    }
    else
        return 3;
}

void output(int fd)
{
    char str[N];
    int n;
    while ((n = read(fd, str, N)) > 0)
        write(1, str, n);
}

void outplus(int fd, int count)
{
    if (count == 0)
        return;

    int n = 0, col;

    char c;

    while (count - 1 != n)
    {
        col = read(fd, &c, 1);
        if (col == 0)
            return;
        // printf("%c", c);
        if (c == '\n')
            ++n;
    }

    output(fd);
}

int filecounter(int fd, int count)
{
    char c = 0;
    int n = 0, col = 1;

    while (count != n)
    {
        col = read(fd, &c, 1);
        if (col == 0)
        {
            lseek(fd, 0, SEEK_SET);
            return 0;
        }
        if (c == '\n')
            ++n;
    }
    lseek(fd, 0, SEEK_SET);
    return 1;
}

void outpmin(int count, int fd)
{
    if (count == 0)
        return;

    int n = 0, col;

    char c;

    while (count != n)
    {
        col = read(fd, &c, 1);
        if (col == 0)
            break;
        lseek(fd, -2, SEEK_CUR);
        // printf("%c", c);
        if (c == '\n')
            ++n;
    }

    lseek(fd, 2, SEEK_CUR);

    output(fd);
}

int main(int argc, char **argv)
{
    int mode, fd = 0;
    long count;

    if (argc > 1)
        mode = getmode(argv[1], &count);

    if (argc == 3)
    {
        if (mode < 3)
            fd = open(argv[2], O_RDONLY);
        else
            fd = open(argv[1], O_RDONLY);

        if (fd <= 0)
        {
            printf("Invalid use of tail");
            return 0;
        }
    }
    else if (argc > 3)
    {
        printf("Invalid use of tail");
        return 0;
    }
    else
    {
        if (argc == 2 && mode == 3)
            fd = open(argv[1], O_RDONLY);
    }

    if (filecounter(fd, count))
        if (mode % 2)
        {
            // printf("0000");
            lseek(fd, -1, SEEK_END);
            outpmin(count, fd);
        }
        else
            outplus(fd, count); // printf("4444");
    else
        if (mode % 2)
            output(fd);

    return 0;
}
