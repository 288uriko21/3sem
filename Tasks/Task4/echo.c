#include <string.h>
#include <unistd.h>
#include <stdio.h>

void writeE(char *str)
{
    if (str)
        while (*str)
        {
            if (*str == '\\')
            {
                ++str;
                switch (*str)
                {
                case 'n':
                    write(1, "\n", 1); 
                    break;
                case 't':
                    write(1, "\t", 1);
                    break;
                case 'v':
                    write(1, "\v", 1);
                    break;
                case 'b':
                    write(1, "\b", 1);
                    break;
                case 'r':
                    write(1, "\r", 1);
                    break;
                default:
                    write(1, "\\", 1);
                    write(1, str, 1);
                }
            }
            else
                write(1, str, 1);
            ++str;
        }
}

int main(int argc, char **argv)
{
    int e = 0;
    int n = 1;
    int cycle_count = 1;

    if (argc <= 1)
    {
        write(1, "\n", 1);
        return 0;
    }

    for (int i = 1; i <= argc; i++)
        if (argv[i][0] == '-')
        {
            if (!strcmp("-n", argv[i]))
            {
                n = 0;
                ++cycle_count;
            }
            else if (!strcmp("-e", argv[i]))
            {
                e = 1;
                ++cycle_count;
            }
            else if (!strcmp("-E", argv[i]))
            {
                e = 0;
                ++cycle_count;
            }
            else
                break;
        }
        else
            break;

    for (; cycle_count < argc; ++cycle_count)
    {
        if (e)
            writeE(argv[cycle_count]);
        else
            write(1, argv[cycle_count], sizeof(argv[cycle_count]));
        if (cycle_count != argc - 1)
            write(1, " ", 1);
    }
    if (n)
        write(1, "\n", 1);

    return 0;
}
