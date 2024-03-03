#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#include <sys/wait.h>

int main()
{
	pid_t child;
	child = fork();
	if(child < 0)
	{
		printf("Fork failed");
	}
	else if(child == 0)
	{
		printf("Child process pid = %d \nParent process pid = %d\n", getpid(),getppid());
		printf("Child process terminated\n");
		exit(0);
	}
	else
	{
		pid_t w = wait(NULL);
		printf("Parent process terminated\n");
        printf("Wait is %d\n",w);
	
  }

}
