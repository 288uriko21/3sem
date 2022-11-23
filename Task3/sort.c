void mysort(int i, int j, char **lst, char **lstr)
{
    if (j <= i)
        return; 

    int mid = (i + j) / 2;

    
    mysort(i, mid, lst, lstr);     // sort the left sub-array recursively
    mysort(mid + 1, j, lst, lstr); // sort the right sub-array recursively

    int pointer_left = i;        // pointer_left points to the beginning of the left sub-array
    int pointer_right = mid + 1; // pointer_right points to the beginning of the right sub-array
    int k;                       // k is the loop counter

    
    for (k = i; k <= j; k++)
    {
        if (pointer_left == mid + 1)
        { 
            lstr[k] = lst[pointer_right];
            pointer_right++;
        }
        else if (pointer_right == j + 1)
        { 
            lstr[k] = lst[pointer_left];
            pointer_left++;
        }
        else if (strcmp(lst[pointer_left], lst[pointer_right]) < 0)
        { 
            lstr[k] = lst[pointer_left];
            pointer_left++;
        }
        else
        { 
            lstr[k] = lst[pointer_right];
            pointer_right++;
        };
    }

    for (k = i; k <= j; k++)
    { 
        lst[k] = lstr[k];
    }
}