#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word *link;

typedef struct word
{
    char elem[1000];
    link next;
} word;

void inputList(link *k, link *wr1) /*accepts a link
 to the last element and to the beginning of the list*/
{
    word *wr;
    *k = (word *)malloc(sizeof(word));
    wr = *k;
    while (scanf("%s", wr->elem) != -1)
    {
        wr->next = (word *)malloc(sizeof(word));
        *wr1 = wr;
        wr = wr->next;
    };

    free(wr);
    if (*k == wr)
        *k = NULL;
    else
        (*wr1)->next = NULL;
}

void DeleteSimLast(link *k, link *wr1)
{
    link wr, wrp;
    wr = *k;
    wrp = wr;
    while (wr != *wr1)
    {
        if (!strcmp(wr->elem, (*wr1)->elem))
        {
            if (wr == *k)
            {
                *k = wr->next;
                free(wr);
                wr = *k;
            }
            else
            {
                wrp->next = wr->next;
                free(wr);
                wr = wrp->next;
            }
        }
        else
        {
            wrp = wr;
            wr = wr->next;
        }
    }
}

void outputListWithFree(link k) 
{
    link wr, wrp;
    wr = k;
    wrp = wr;
    while (wr != NULL)
    {
        wrp = wr;
        printf("%s ", wr->elem);
        wr = wr->next;
        free(wrp);
    };
}


int main(void)
{
    word *k /*root*/;
    word *wr1 /*last word*/, *wrp /*previous word*/;

    inputList(&k, &wr1);

    if (k != NULL)
    {
        DeleteSimLast(&k, &wr1);
        printf("\n");
        outputListWithFree(k);
        printf("\n");
    }

    return 0;
}
