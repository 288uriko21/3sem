#include <stdio.h>
#include <stdlib.h>

typedef struct word *link;

typedef struct word
{
    char elem[1000];
    link next;
} word;

int comp(char *s1, char *s2)
{
    while (*s1 != '\0' || *s2 != '\0')
    {
        if (*s1 != *s2)
            return 0;
        s1++;
        s2++;
    };
    return 1;
} /*word comparison*/

int main(void)
{
    word *wr;
    word *k/*root*/;
    word *wr1/*last word*/, *wrp/*previous word*/;
    k = (word *)malloc(sizeof(word));
    wr = k;
    while (scanf("%s", wr->elem) != -1)
    {
        wr->next = (word *)malloc(sizeof(word));
        wr1 = wr;
        wr = wr->next;
    };

    free(wr);
    if (k == wr)
        return 0;

    wr1->next = NULL;

    wr = k;
    wrp = wr;
    while (wr != wr1)
    {
        if (comp(wr->elem, wr1->elem))
        {
            if (wr == k)
            {
                k = wr->next;
                free(wr);
                wr = k;
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
    };

    printf("\n");
    wr = k; 
    wrp = wr;
    while (wr != NULL)
    {
        wrp = wr;
        printf("%s ", wr->elem);
        wr = wr->next;
        free(wrp);
    };

    printf("\n");

    return 0;
}