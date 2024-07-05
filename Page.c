#include<stdio.h>
#include<stdlib.h>

int n,f,i,j,k,p,fault=0,flag;

void printframe(int frames[],int size) {
    int i; 
    for(i=0;i<size;i++) {
        printf(" |%d|\n",frames[i]); 
    }
    printf("\n\n"); 
}

void fifo(int pages[],int n,int realframes[],int f) {
    int frames[f]; 
    for(j=0;j<f;j++) {
        frames[j]=realframes[j]; 
    }
    printf("\tFIFO page replacement\n"); 
    fault=0;
    k=0;
    for(i=0;i<n;i++) {
        p=pages[i];
        flag=1; 
        for(j=0;j<f;j++) {
            if (p==frames[j]) {
                flag=0;
                break; 
            }
        }
        if (flag==1) {
            fault++;
            frames[k]=p; 
            k=(k+1)%f; 
            printframe(frames,f);
        } else {
            printframe(frames,f); 
        }
    }
    printf("Total page fault is :%d",fault);
}

void lfu(int pages[],int n,int realframes[],int f) {
    int min;
    int frames[f],freq[f]; 
    for(j=0;j<f;j++) {
        frames[j]=realframes[j];
        freq[j]=0; 
    }
    printf("\tLFU page replacement\n"); 
    fault=0;
    for(i=0;i<n;i++) {
        p=pages[i]; 
        flag=1; 
        for(j=0;j<f;j++) {
            if (p==frames[j]) {
                flag=0; 
                freq[j]++; 
                break;
            } 
        }
        if (flag==1) {
            fault++; 
            min=0; 
            for(j=1;j<f;j++) {
                if (freq[j] < freq[min]) {
                    min=j; 
                }
            }
            frames[min]=p; 
            freq[min]=1; 
            printframe(frames,f);
        } else {
            printframe(frames,f); 
        }
    }
    printf("Total no of page fault is: %d",fault); 
}

void lru(int pages[],int n,int realframes[],int f) {
    int min;
    int frames[f],recent[f]; 
    for(j=0;j<f;j++) {
        frames[j]=realframes[j];
        recent[j]=0; 
    }
    fault=0;
    k=1; 
    for(i=0;i<n;i++) {
        p=pages[i]; 
        flag=1; 
        for(j=0;j<f;j++) {
            if (p==frames[j]) {
                flag=0;
                recent[j]=k; 
                k++;
                break;
            } 
        }
        if (flag==1) {
            fault++; 
            min=0; 
            for(j=1;j<f;j++) {
                if (recent[j] < recent[min]) {
                    min=j; 
                }
            }
            frames[min]=p; 
            recent[min]=k; 
            k++; 
            printframe(frames,f);
        } else {
            printframe(frames,f); 
        }
    }
    printf("Total page fault is : %d",fault); 
}

int main() {
    int ch;
    printf("Enter the total no of pages"); 
    scanf("%d",&n);
    printf("Enter the total no of frames"); 
    scanf("%d",&f);
    int pages[n],realframes[f]; 
    printf("Enter the page sequence"); 
    for(i=0;i<n;i++) {
        scanf("%d",&pages[i]); 
    }
    for(j=0;j<f;j++) {
        realframes[j]=-1; 
    }
    while (1) {
        printf("\n\n"); 
        printf("1.FIFO\n"); 
        printf("2.LFU\n"); 
        printf("3.LRU\n"); 
        printf("4.EXIT\n"); 
        printf("Enter a choice:");
        scanf("%d",&ch); 
        switch(ch) {
            case 1:
                fifo(pages,n,realframes,f);
                break; 
            case 2:
                lfu(pages,n,realframes,f);
                break; 
            case 3:
                lru(pages,n,realframes,f);
                break; 
            case 4:
                exit(0); 
                break; 
            default:
                printf("INVALID CHOICE\n");
                break; 
        }
    }
    return 1; 
}



------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

int i,j,n,f,fault,k,flag;

void printframes(int frames[], int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("-\t");
        else
            printf("%d\t", frames[i]);
    }
    printf("\n");
}

void fifo(int p, int pages[],int f)
{
    int i=n,j,frames[f];
    for(j=0;j<f;j++)
    {
        frames[j] = -1;
    }
    fault=0;
    k=0;
    for(i=0;i<n;i++)
    {
        p=pages[i];
        flag=1;
        for(j=0;j<f;j++)
        {
            if(p==frames[j])
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
        {
            fault++;
            frames[k] = p;
            k=(k+1)%f;
            printfframes(frames,f);
        }
        else
            printfframes(frames,f);
    }
    printf("Total page fault is :%d",fault);
    
}

int main()
{
    printf("Enter the total no of pages"); 
    scanf("%d",&n);
    printf("Enter the total no of frames"); 
    scanf("%d",&f);
    int pages[n]; 
    printf("Enter the page sequence"); 
    for(i=0;i<n;i++) {
        scanf("%d",&pages[i]); 
    }
    fifo(n,pages,f);
}    
