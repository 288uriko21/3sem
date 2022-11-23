#include <stdio.h>
//#include <io.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <limits.h>

void add(char **mas, char *str, int op, char *par)
{
    int ln = strlen(par);
    int ln2 = strlen(str);
    mas = (char **)realloc(mas, (sizeof(char *) * (op+1)));
    mas[op] = (char *)malloc(ln + ln2 + 1);
    strncpy(mas[op], par, ln);
    strncat(mas[op], "/", ln+1);
    strncat(mas[op], str, ln + ln2 + 1);
    //strncat(mas[op], "\0", ln2 + ln + 2);
    printf("\n%s\n", mas[op]);
    return;
}

void doR(char **mas, int col, int op, int dirs, char* start)
{
    if (col < 1)
        return;
    --col;
    // printf(mas[op]);
    DIR *d = opendir(*(mas+op));
    chdir(mas[op]);
    ++op;
    struct dirent *dd;
    printf("%s:\n", mas[op - 1]);
    struct stat *buf = (struct stat *)malloc(sizeof(struct stat));
    while ((dd = readdir(d)) != NULL)
    {
        if (strcmp(dd->d_name, ".") && strcmp(dd->d_name, ".."))
        {
            printf("%s   ", dd->d_name);
            stat(dd->d_name, buf);
            if (S_ISDIR(buf->st_mode))
            {
                add(mas, dd->d_name, dirs, mas[op-1]);
                //printf("\n%s\n", *(mas+dirs-1));
                ++col;
                ++dirs;
            }
        }
    }
    free(buf);
    closedir(d);
    printf("\n\n");
    chdir(start);
    doR(mas, col, op, dirs, start);
}

int getmode(char *str)
{

    if (str[0] == '-')
    {
        if (strlen(str) > 2)
            return 0;
        if (str[1] == 'l')
            return 2;
        if (str[1] == 'R')
            return 3;
        if (str[1] == 'g')
            return 4;
    }
    else
        return 0;
}

int main(int argc, char **argv)
{
    int mode = 1;
    char s_mode[10] = "drwxrwxrwx";

    if (argc > 2)
    {
        printf("Invalid use of ls");
        return 0;
    }
    if (argc > 1)
        mode = getmode(argv[1]);

    if (!mode)
    {
        printf("Invalid use of ls");
        return 0;
    }

    struct dirent *dd;
    mode = 3; /////////////////////////////////////////////////////////////////////////
    switch (mode)
    {
    case 1:
    {
        DIR *d = opendir(".");
        while ((dd = readdir(d)) != NULL)
        {
            if (strcmp(dd->d_name, ".") && strcmp(dd->d_name, ".."))
                printf("%s     ", dd->d_name);
        }
        printf("\n");
    }
    break;
    case 2:
    case 4:
    {

        DIR *d = opendir(".");
        struct stat *buf = (struct stat *)malloc(sizeof(struct stat));
        struct passwd *st = (struct passwd *)malloc(sizeof(struct passwd));
        struct group *stt = (struct group *)malloc(sizeof(struct group));
        while ((dd = readdir(d)) != NULL)
        {
            if (strcmp(dd->d_name, ".") && strcmp(dd->d_name, ".."))
            {
                int count = 0;               
                lstat(dd->d_name, buf);
                int accss = buf->st_mode;

                /*if (S_ISREG(buf->st_mode))
                    printf("-");
                else
                    printf("d");*/
                if (S_ISDIR(buf->st_mode))
                    printf("d");
                else
                    printf("-");

                if (S_IRUSR & buf->st_mode)
                    printf("r");
                else
                    printf("-");

                if (S_IWUSR & buf->st_mode)
                    printf("w");
                else
                    printf("-");

                if (S_IXUSR & buf->st_mode)
                    printf("x");
                else
                    printf("-");

                if (S_IRGRP & buf->st_mode)
                    printf("r");
                else
                    printf("-");

                if (S_IWGRP & buf->st_mode)
                    printf("w");
                else
                    printf("-");

                if (S_IXGRP & buf->st_mode)
                    printf("x");
                else
                    printf("-");

                if (S_IROTH & buf->st_mode)
                    printf("r");
                else
                    printf("-");

                if (S_IWOTH & buf->st_mode)
                    printf("w");
                else
                    printf("-");

                if (S_IXOTH & buf->st_mode)
                    printf("x");
                else
                    printf("-");

                printf(" %lu", buf->st_nlink);
                /*printf(" %s", buf->st_uid);
                printf(" %s", buf->st_gid);
                printf(" %s", buf->st_size);
                printf(" %s", buf->st_mtime);*/
                if (mode == 2)
                {
                    st = getpwuid(buf->st_uid);
                    printf(" %s", st->pw_name);
                }
                // free((void *)st);

                stt = getgrgid(buf->st_gid);
                printf(" %s", stt->gr_name);
                // free(stt);
                printf(" %*ld", 8, buf->st_size);
                // printf(" %s", ctime(&(buf->st_mtime)));

                /*struct ftime ft;
                int df = fopen(dd->d_name, O_RDONLY);
                getftime(, &ft);
                printf("%02u %02u", ft.ft_month, ft.ft_day);
                printf("%02u:%02u",ft.ft_hour, ft.ft_min, ft.ft_tsec);
                close(fd);*/
                printf(" %*s", 10, dd->d_name);
                printf("\n");

                // free(buf);
            }
        }
    }
    break;
    case 3:
    {
        char **mas;
        char *start;
        mas = (char **)malloc(sizeof(char *));
        mas[0] = (char *)malloc(3);
        mas[0] = ".\0";
        start = (char*)malloc(PATH_MAX);
        start = realpath(".", start);
        doR(mas, 1, 0, 1, start);
    }
    break;
    default:
        break;
    }
    return 0;
}