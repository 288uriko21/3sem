#include <stdio.h>
#include <stdlib.h>

typedef struct elem *link;

typedef struct elem
{
  unsigned int num;
  link right;
  link left;
} elem;

void myfree(link k)
{
  if (k != NULL)
  {
    if (k->right != NULL)
      myfree(k->right);
    if (k->left != NULL)
      myfree(k->left);
    free(k);
  }
}

link plus(unsigned int el, link k)
{
  link res = k, parent;
  if (k == NULL)
  {
    k = (link)malloc(sizeof(elem));
    res = k;
    k->num = el;
    k->right = NULL;
    k->left = NULL;
  }
  else
  {
    while (k != NULL)
    {
      parent = k;
      if (k->num == el)
        return res;
      if (k->num > el)
      {
        if (k->left == NULL)
        {
          k->left = (link)malloc(sizeof(elem));
          k = k->left;
          break;
        }
        else
          k = k->left;
      }
      else if (k->right == NULL)
      {
        k->right = (link)malloc(sizeof(elem));
        k = k->right;
        break;
      }
      else
        k = k->right;
    };
    k->num = el;
    k->right = NULL;
    k->left = NULL;
    return res;
  };
};

int quest(unsigned int el, elem *k)
{
  while (k != NULL)
  {
    if (k->num == el)
      return 1;
    if (k->num > el)
      k = k->left;
    else
      k = k->right;
  };
  return 0;
};

link minus(unsigned int el, elem *k)
{
  elem *parent = k, *res = k; /*k - the element to be deleted (replaced)*/
  while (k != NULL)
  {
    if (k->num == el)
      break;
    parent = k;
    if (k->num > el)
      k = k->left;
    else
      k = k->right;
  };
  if (k == NULL)
    return res;

  if (k->right == NULL && k->left == NULL) // case 1
  {
    if (parent->right == k)
    {
      free(parent->right);
      parent->right = NULL;
    };
    if (parent->left == k)
    {
      free(parent->left);
      parent->left = NULL;
    }
    if (k == parent){
      free(k);
      res = NULL;
    }
    return res;
  }
  else // case 2
  {
    if (k->right == NULL)
    {
      if (parent->right == k)
      {
        parent->right = k->left;
        free(k);
      };
      if (parent->left == k)
      {
        parent->left = k->left;
        free(k);
      };
      if (k == parent)
      {
        res = k->left;
        free(k);
      }
      return res;
    };
    if (k->left == NULL)
    {
      if (parent->right == k)
      {
        parent->right = k->right;
        free(k);
      };
      if (parent->left == k)
      {
        parent->left = k->right;
        free(k);
      };
      if (k == parent)
      {
        res = k->right;
        free(k);
      }
      return res;
    };
  };

  elem *replace = k->right; /*the element to put in place of the deleted*/
  elem *parRep = k;
  while (replace->left != NULL) // case 3
  {
    parRep = replace;
    replace = replace->left;
  };
  k->num = replace->num;
  if (replace->right == NULL)
  {
    if (parRep != k)
      parRep->left = NULL;
    else
      parRep->right = NULL;
  }
  else
  {
    if (parRep != k)
      parRep->left = replace->right;
    else
      parRep->right = replace->right;
  }
  free(replace);
  return res;
};

int main(void)
{
  link root = NULL;
  char simv;
  unsigned int a;
  while (scanf("%c", &simv) != -1)
  {
    switch (simv)
    {
    case '+':
      scanf("%u", &a);
      root = plus(a, root);
      break;
    case '-':
      scanf("%u", &a);
      root = minus(a, root);
      break;
    case '?':
      scanf("%u", &a);
      if (quest(a, root))
        printf("\n%u yes\n", a);
      else
        printf("\n%u no\n", a);
      break;
    }
  };
  if (root != NULL)
    myfree(root);
  return 0;
}