#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sort.c"
#define SIZE 16
#define N 10

// vertex
static int c;        /*current symbol */
static char **lst, **lstr;   /* list of words (in the form of an array)*/
static char *buf;    /* buffer for accumulating the current word*/
static int sizebuf;  /* buffer size of the current word*/
static int sizelist; /* word list size*/
static int curbuf;   /* index of the current symbol in the buffer*/
static int curlist;  /* index of the current word in the list*/
static char cprev;
typedef void *(*vertex)();


static void *start();   //   states in the diagram
static void *word();
static void *greater();
static void *greater2();
static void *newline();
static void *stop();

static void clearlist();  
static void null_list();  // lines in the diagram
static void termlist();
static void nullbuf();
static void addsym();
static void addword();
static void printlist();
static int symset(int c);
static char getsym(); 

void graph()
{
    vertex V = start;
    c = getsym();
    null_list();
    while (1)
        V = V();
}

static void *start()
{
    if (c == ' ' || c == '\t')
    {
        c = getsym();
        return start;
    }
    else if (c == EOF)
    {
        termlist();
        //printlist();
        clearlist();
        return stop;
    }
    else if (c == '\n')
    {
        termlist();
        //printlist(); so it was in the example
        c = getsym();
        return newline;
    }
    else
    {
        cprev = c;
        nullbuf();
        addsym();
        c = getsym();
        return (cprev == '>' || cprev == '<' || cprev == '&' || cprev == '|' || cprev == ')' || cprev == '(' || cprev == ';') ? greater : word;
    }
}

static void *word()
{
    if (symset(c))
    {
        addsym();
        c = getsym();
        return word;
    }
    else
    {
        addword();
        return start;
    }
}

static void *greater()
{
    if (c == cprev && c != ')' && c != '(' && c!='<' && c!=';')
    {
        addsym();
        c = getsym();

        return greater2;
    }
    else
    {
        addword();
        return start;
    }
}

static void *greater2()
{
    addword();
    return start;
}

static void *newline()
{
    clearlist();
    return start;
}

static void *stop()
{
    exit(0);
}


static char getsym()
{
    static char str[N];
    static int n = N;

    if (n == N)
    {
        n = 0;
        for (int i = 0; i < N; ++i)
            str[i] = '\n';

        if (!feof(stdin))
        {
            char s[30];
            sprintf(s, "%%%dc", N);
            fscanf(stdin, s, str);
        }
        else
            return EOF;
    }

    return str[n++];
}

static void clearlist()
{
    int i;
    sizelist = 0;
    curlist = 0;
    if (lst == NULL)
        return;
    for (i = 0; lst[i] != NULL; i++)
        free(lst[i]);
    free(lst);
    free(lstr);
    lst = NULL;
}

static void null_list()
{
    sizelist = 0;
    curlist = 0;
    lst = NULL;
}

static void termlist()
{
    if (lst == NULL)
        return;
    if (curlist > sizelist - 1)
        lst = realloc(lst, (sizelist + 1) * sizeof(*lst));
    lst[curlist] = NULL;
    /*align the memory used for the list exactly to the size of the list*/
    lst = realloc(lst, (sizelist = curlist + 1) * sizeof(char *));
    lstr = (char **)malloc((sizelist) * sizeof(char *));
    printf("%d\n", sizelist - 1);
    printlist();
    mysort(0, sizelist - 2, lst, lstr);
    printf("%d\n", sizelist - 1);
    printlist();
}

static void nullbuf()
{
    buf = NULL;
    sizebuf = 0;
    curbuf = 0;
}

static void addsym()
{
    if (curbuf > sizebuf - 1)
        buf = realloc(buf, sizebuf += SIZE); /* increase the buffer
if necessary */
    buf[curbuf++] = c;
}

static void addword()
{
    if (curbuf > sizebuf - 1)
        buf = realloc(buf, sizebuf += 1); /* to write ’\0’, increase the buffer
if necessary */
    buf[curbuf++] = '\0';

    /*align the memory used exactly to the size of the word*/
    buf = realloc(buf, sizebuf = curbuf);
    if (curlist > sizelist - 1)
        lst = realloc(lst, (sizelist += SIZE) * sizeof(*lst)); 
    lst[curlist++] = buf;
}

static void printlist()
{
    int i;
    if (lst == NULL)
        return;

    for (i = 0; i < sizelist - 1; i++)
        printf("%s\n", lst[i]);
}

static int symset(int c)
{
    return c != '\n' &&
           c != ' ' &&
           c != '\t' &&
           c != '>' &&
           c != '<' &&
           c != '&' &&
           c != '|' &&
           c != ')' &&
           c != '(' &&
           c != ';' &&
           c != EOF;
}


