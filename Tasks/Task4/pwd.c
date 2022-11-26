#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char *buf = NULL;
    buf = getcwd(buf, 0);
    write(1, buf, strlen(buf)+1);
    write(1, "\n", 1);
    free(buf);
    return 0;
}
