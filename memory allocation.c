#include <stdio.h>
#include <stdlib.h>

#define max 1000
#define min 0

int n, m, p_size[10], b_size[10], filled[10], alloc[10];

void display()
{
    int i;
    printf("ProcessNo\tProcessSize\tAllocBlock\n");
    for (i = 0; i < n; i++)
    {
        if (alloc[i] == -1)
        {
            printf("%d\t\t%d\t\tNIL\n", i, p_size[i]);
        }
        else
        {
            printf("%d\t\t%d\t\t%d\n", i, p_size[i], alloc[i]);
        }
    }
    printf("\n");
}

void int_frag(int temp[])
{
    int i;
    printf("BlockNo\t\tInternalFragmentation\n");
    for (i = 0; i < m; i++)
    {
        if (filled[i])
        {
            printf("%d\t\t%d\n", i, temp[i]);
        }
        else
        {
            printf("%d\t\tNIL\n", i);
        }
    }
    printf("\n");
}

void ext_frag()
{
    int i;
    printf("External Fragmentation\n");
    printf("BlockNo\t\tBlockSize\n");
    for (i = 0; i < m; i++)
    {
        if (!filled[i])
        {
            printf("%d\t\t%d\n", i, b_size[i]);
        }
    }
    printf("\n");
}

void firstfit()
{
    int temp[10], i, j;
    for (i = 0; i < n; i++)
    {
        alloc[i] = -1;
    }
    for (j = 0; j < m; j++)
    {
        temp[j] = b_size[j];
        filled[j] = 0;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (!filled[j] && b_size[j] >= p_size[i])
            {
                alloc[i] = j;
                filled[j] = 1;
                temp[j] -= p_size[i];
                break;
            }
        }
    }
    printf("\nFIRST FIT\n");
    display();
    int_frag(temp);
    ext_frag();
}

void best_fit()
{
    int i, j, best_index, temp[10];
    for (i = 0; i < n; i++)
        alloc[i] = -1;

    for (j = 0; j < m; j++)
    {
        filled[j] = 0;
        temp[j] = b_size[j];
    }

    for (i = 0; i < n; i++)
    {
        best_index = -1;
        for (j = 0; j < m; j++)
        {
            if (!filled[j] && b_size[j] >= p_size[i])
            {
                if (best_index == -1)
                    best_index = j;
                else if (b_size[j] < b_size[best_index])
                    best_index = j;
            }
        }
        if (best_index != -1)
        {
            alloc[i] = best_index;
            filled[best_index] = 1;
            temp[best_index] -= p_size[i];
        }
    }
    printf("\nBEST FIT\n");
    display();
    int_frag(temp);
    ext_frag();
}

void worstfit()
{
    int i, j, temp[10], worst_index;
    for (i = 0; i < n; i++)
    {
        alloc[i] = -1;
    }
    for (j = 0; j < m; j++)
    {
        filled[j] = 0;
        temp[j] = b_size[j];
    }
    for (i = 0; i < n; i++)
    {
        worst_index = -1;
        for (j = 0; j < m; j++)
        {
            if (!filled[j] && b_size[j] >= p_size[i])
            {
                if (worst_index == -1 || b_size[j] > b_size[worst_index])
                {
                    worst_index = j;
                }
            }
        }
        if (worst_index != -1)
        {
            alloc[i] = worst_index;
            filled[worst_index] = 1;
            temp[worst_index] -= p_size[i];
        }
    }
    printf("\nWORST FIT\n");
    display();
    int_frag(temp);
    ext_frag();
}

int main()
{
    int i;
    printf("How many processes? ");
    scanf("%d", &n);
    printf("How many blocks? ");
    scanf("%d", &m);

    printf("Enter the size of %d processes:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &p_size[i]);

    printf("Enter the size of %d blocks:\n", m);
    for (i = 0; i < m; i++)
        scanf("%d", &b_size[i]);

    firstfit();
    best_fit();
    worstfit();

    return 0;
}
