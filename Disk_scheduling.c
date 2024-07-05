//DISK SCHEDULING ALGO

#include <stdio.h>
#include <stdlib.h>

int n,r[25],temp[25],initial,size;

void fcfs()
{
    int i,current=initial,seek=0;
    for(i=0;i<n;i++)
    {
        seek+=abs(r[i]-current);
        current=r[i];
    }
    printf("FCFS Total head movement(seek time) : %d\n",seek);
}

void sstf()
{
    int i,j,min_index,current=initial,seek=0,min_distance;
    int visited[n];
    for(i=0;i<n;i++)
    {
        visited[i] = 0;
    }
    for(i=0;i<n;i++)
    {
        min_distance=1000000;
        for(j=0;j<n;j++)
        {
            if(visited[j]==0 && abs(current - r[j]) < min_distance)
            {
                min_distance=abs(current - r[j]);
                min_index=j;
            }
        }
        visited[min_index]=1;
        seek+=min_distance;
        current=r[min_index];
    }

    printf("SSTF Total head movement(seek time) : %d\n", seek);
}

void scan()
{
    int i,j,temp_v,current=initial,seek=0,index;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j] > temp[j+1])
            {
                temp_v=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_v;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(current < temp[i])
        {
            index=i;
            break;
        }
    }
    for(i=index;i<n;i++)
    {
        seek+=abs(temp[i]-current);
        current=temp[i];
    }
    seek+=abs(size-1-current);
    current=size-1;
    for(i=index-1;i>=0;i--)
    {
        seek+=abs(current-temp[i]);
        current=temp[i];
    }
    printf("SCAN Total head movement(seek time) : %d\n",seek);
}

void cscan()
{
    int i,j,temp_v,current=initial,seek=0,index;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j] > temp[j+1])
            {
                temp_v=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_v;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(current < temp[i])
        {
            index=i;
            break;
        }
    }
    for(i=index;i<n;i++)
    {
        seek+=abs(temp[i]-current);
        current=temp[i];
    }
    seek+=abs(size-1-current);
    current=size-1;
    seek+=current;
    current=0;
    for(i=0;i<index;i++)
    {
        seek+=abs(temp[i]-current);
        current=temp[i];
    }
    printf("CSCAN Total head movement(seek time) : %d\n",seek);
}

void look()
{
    int i,j,temp_v,current=initial,seek=0,index;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j] > temp[j+1])
            {
                temp_v=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_v;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(current < temp[i])
        {
            index=i;
            break;
        }
    }
    for(i=index;i<n;i++)
    {
        seek+=abs(temp[i]-current);
        current=temp[i];
    }
    for(i=index-1;i>=0;i--)
    {
        seek+=abs(current-temp[i]);
        current=temp[i];
    }
    printf("LOOK Total head movement(seek time) : %d\n",seek);
}

void clook()
{
    int i,j,temp_v,current=initial,seek=0,index;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j] > temp[j+1])
            {
                temp_v=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_v;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(current < temp[i])
        {
            index=i;
            break;
        }
    }
    for(i=index;i<n;i++)
    {
        seek+=abs(temp[i]-current);
        current=temp[i];
    }
    seek+=current-temp[0];
    current=temp[0];
    for(i=1;i<index;i++)
    {
        seek+=abs(current-temp[i]);
        current=temp[i];
    }
    printf("CLOOK Total head movement(seek time) : %d\n",seek);
}

int main()
{
    int i;
    printf("How many requests ? : ");
    scanf("%d",&n);
    printf("Enter the request sequence : ");
    for(i=0;i<n;i++)
    {
        scanf("%d",&r[i]);
    }
    for(i=0;i<n;i++)
    {
        temp[i]=r[i];
    }
    printf("Enter the total disk size : ");
    scanf("%d",&size);
    printf("Enter the initial head position : ");
    scanf("%d",&initial);
    fcfs();
    scan();
    cscan();
    look();
    clook();
    sstf();
}


---------------_-------_-_----------------__----_-----__


    #include <stdio.h>

int getSeekTime(int a,int b){
	if(a>b)
		return a-b;
	return b-a;
}

void copy(int arr[],int temp[],int n){
	for(int i=0;i<n;i++)
		temp[i] = arr[i];
}

void sort(int arr[],int n){
	int temp;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int reqIndex(int arr[],int n,int p){
	for(int i=0;i<n;i++){
		if(arr[i]>=p)
			return i;
	}
}

void fcfs(int arr[],int n,int p,int max){
	printf("\nFCFS Disk Scheduling\n");
	int seekTime=0;
	printf("%d => ",p);
	for(int i=0;i<n;i++){
		seekTime += getSeekTime(p,arr[i]);
		if(i!=n-1)
			printf("%d => ",arr[i]);
		else
			printf("%d",arr[i]);
		p = arr[i];
	}
	printf("\nTotal Head Movements in FCFS = %d\n\n",seekTime);
}

void scan(int arr[],int n,int p,int max){
	printf("\nSCAN Disk Scheduling\n");
	int seekTime=0,temp[n],i;
	copy(arr,temp,n);
	sort(temp,n);
	int index = reqIndex(temp,n,p);

	seekTime+=getSeekTime(p,max);

	printf("%d => ",p);
	for( i=index;i<n;i++){
		printf("%d => ",temp[i]);
		p=temp[i];
	}
	printf("%d\n%d => ",max,max);
	p=max;
	for( i=index-1;i>=0;i--){
		if(i!=0)
			printf("%d => ",temp[i]);
		else
			printf("%d",temp[i]);
		p=temp[i];
	}
	seekTime+=getSeekTime(max,temp[0]);
	printf("\nTotal Head Movements in SCAN = %d\n\n",seekTime);
}

void cscan(int arr[],int n,int p,int max){
	printf("\nCSCAN Disk Scheduling\n");
	int seekTime=0,temp[n],i;
	copy(arr,temp,n);
	sort(temp,n);
	int index = reqIndex(temp,n,p);

	seekTime+=getSeekTime(p,max);

	printf("%d => ",p);
	for( i=index;i<n;i++){
		printf("%d => ",temp[i]);
		p=temp[i];
	}
	printf("%d \n0 => ",max);
	p=0;
	for( i=0;i<index;i++){
		if(i!=index-1)
			printf("%d => ",temp[i]);
		else
			printf("%d",temp[i]);
		p=temp[i];
	}
	seekTime+=getSeekTime(max,0);
	if(index>0)
		seekTime+=getSeekTime(0,temp[index-1]);
	printf("\nTotal Head Movements in CSCAN = %d\n\n",seekTime);
}

void main(){
	printf("DISK SCHEDULING\n");
	int n,position,i,min,max,p;
	printf("Enter the disk track limit(max): ");
	scanf("%d",&max);
	printf("Enter the number of requests: ");
	scanf("%d",&n);
	printf("Enter the requests \n");
	int arr[n];
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	printf("Enter the current position of disk arm: ");
	scanf("%d",&p);
	int choice;
	do{
		printf("1. FCFS\n");
		printf("2. SCAN\n");
		printf("3. CSCAN\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);

		switch(choice){
			case 1: 
				fcfs(arr,n,p,max);
				break;
			case 2:
				scan(arr,n,p,max);
				break;
			case 3: 
				cscan(arr,n,p,max);
				break;
			case 4: 
				break;
			default:
				printf("invalid input\n");
				break;
		}
	}while(choice<4);
}
