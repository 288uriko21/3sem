#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
    struct Node *prev, *next;
    char elem[10];
};

struct List
{
    struct Node *first, *last;
};

void rebinding(struct Node *del)
{
    if (del->prev != NULL)
        del->prev->next = del->next;
    if (del->next != NULL)
        del->next->prev = del->prev;
};

void process(struct List *pl, const char *str)
{
    int res, flag = 1;
    if (pl->first == NULL)
        return;
    pl->first->prev = NULL;
    pl->last->next = NULL;
    struct Node *cur = pl->first, *del, *finz = NULL;
    do
    {
        res = strcmp(cur->elem, str);
        del = cur;
        if (cur != finz)
            cur = cur->next;
        else
            cur = NULL;

        if (res == 0)
        {
            if (pl->first == del)
                pl->first = del->next;
            if (pl->last == del)
                pl->last = del->prev;

            if (del->prev != NULL)
                del->prev->next = del->next;
            if (del->next != NULL)
                del->next->prev = del->prev;

            // free(del->elem);
            free(del);
        }
        if (res > 0)
        {
            if (pl->last != del && finz != del)
            {

                if (del->prev != NULL)
                    del->prev->next = del->next;
                if (del->next != NULL)
                    del->next->prev = del->prev;

                if (pl->first == del)
                    pl->first = cur;
                if (flag)
                    finz = del;
                flag = 0;
                (pl->last)->next = del;
                del->next = NULL;
                del->prev = pl->last;
                pl->last = del;
            }
        }
    } while (cur != NULL);
}; // он много раз проходит по элементу,
//что нужно переставит и бесконечно переставляет
// добавить количество

int main(void)
{
    struct Node *cur, *root, *cur1;
    cur = (struct Node *)malloc(sizeof(struct Node));
    cur->next = (struct Node *)malloc(sizeof(struct Node));
    // printf("1");
    cur->next->prev = cur;
    cur->prev = NULL;
    // printf("2");
    cur1 = cur;
    root = cur;
    // printf("3");
    scanf("%s", cur->elem);
    cur = cur->next;
    for (int i = 0; i <= -1; ++i)
    {
        cur->next = (struct Node *)malloc(sizeof(struct Node));
        cur->next->prev = cur;
        cur->prev = cur1;
        scanf("%s", cur->elem);
        cur1 = cur;
        cur = cur->next;
    };
    free(cur);
    cur1->next = NULL;

    struct Node *root1 = root, *toor, *root2 = root;

    struct List pl;
    pl.first = root;
    while (root2 != NULL)
    {
        toor = root2;
        root2 = root2->next;
    };
    pl.last = toor;
    char str[10];
    printf("0");
    scanf("%s", str);
    process(&pl, str);

    while (pl.first != NULL)
    {
        // printf("1");
        printf("%s\n", (pl.first)->elem);
        (pl.first) = (pl.first)->next;
    };
    printf("\n");
    while ((pl.last) != NULL)
    {
        // printf("2");
        printf("%s\n", (pl.last)->elem);
        (pl.last) = (pl.last)->prev;
    }

    return 0;
}