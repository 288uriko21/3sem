/* реализовать калькулятор, у которого есть две целые  переменные a и b, любые
   константы и полный набор операций языка Си. Например, он должен уметь
   вычислить  результат Си-выражения    a=1,  b=2, (a+b)^4%2 ? 5: sizeof( 6) .
   Требование дополнительное:  Программа-калькулятор выражений Си не должна
   превышать 10-15  строк. (Да, а то вы наверное подумали, что задача на много
   часов работы : ) . Учтите, что у shell'а синтаксис выражений свой, отличный
   от Си, то есть просто "скормить" выражению shell'у  не получится */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char str[2000];
    char expr[2000];
    int fd;

    fgets(expr, 2000, stdin);
    *strchr(expr,'\n')='\0';
    strcpy(str,"#include <stdio.h>\nint main() {\n\tint a, b;\n\tprintf(\"%lu\\n\", (");
    strcat(str,expr);
    strcat(str,"));\n\treturn 0;\n}\n");
    fd=open("tmptmptmp.c",O_WRONLY|O_TRUNC|O_CREAT,0666);
    write (fd, str, (strchr(str,'\0')-str)*sizeof(char));
    close(fd);
    if (fork()==0)
        execlp("gcc","gcc","tmptmptmp.c","-o","tmptmptmp.out",NULL);
    wait(0);
    remove("tmptmptmp.c");
    if (fork()==0)
        execlp("./tmptmptmp.out","./tmptmptmp.out",NULL);
    wait(0);
    remove("tmptmptmp.out");
    return 0;
}