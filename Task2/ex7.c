#include <stdio.h>
#include <setjmp.h>
jmp_buf begin;
char curlex;
void getlex(void);
int expr(void);
int add(void);
int mult(void);
void error();
int mypow(void);

int main()
{
    int result;
    setjmp(begin);
    printf("==>");
    getlex();
    result = expr();
    if (curlex != '\n')
        error();
    printf("\n%d\n", result);
    return 0;
}

void getlex()
{
    while ((curlex = getchar()) == ' ');
}

void error(void)
{
    printf("\nОшибка!\n");
    while (getchar() != '\n');
    longjmp(begin, 1);
}

int expr()
{
    int e = add();
    while ((curlex == '+') || (curlex == '-'))
    {
        if (curlex == '+')
        {
            getlex();
            e += add();
        }
        if (curlex == '-')
        {
            getlex();
            e -= add();
        }
    }
    return e;
}

int add()
{
    int a = mypow();
    while ((curlex == '*') || (curlex == '/'))
    {
        if (curlex == '*')
        {
            getlex();
            a *= mypow();
        }
        if (curlex == '/')
        {
            getlex();
            a /= mypow();
        }
    }
    return a;
}

int mypow()
{
    int a = mult();
    int a1 = a;
    while (curlex == '^')
    {
        getlex();
        int b = mypow();
        if (b<0)
           error();
        if (b == 0)
           return 1;
        for (int i = 1; i < b; ++i)
            a *= a1;
    }
    return a;
}

int mult()
{
    int m;
    switch (curlex)
    {
    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9': m = curlex - '0'; break;

    case '(':  getlex(); m = expr();
        if (curlex == ')') break;
    default:
        error();
    }
    getlex();
    return m;
}
/*
<выражение> ::= <слагаемое> {+ <слагаемое>} | <слагаемое> {- <слагаемое>}
<слагаемое> ::= <степень> {* <степень>} | <степень> {/ <степень>}
<степень> ::= <множитель> {^ <степень>}
<множитель> ::= 0|1|2|3|4|5|6|7|8|9| (<выражение>)
*/
