#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

            free(del->elem);
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
};