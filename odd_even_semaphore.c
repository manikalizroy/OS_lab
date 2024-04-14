#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int semaphore=1;
int state=1;
void wait(int *semaphore)
//decrements the semaphore value until it becomes greater than 0
{
   while(*semaphore<=0);
   (*semaphore)--;
}
void signal(int *semaphore)
//increments the semaphore value after a delay of 1 second.
{

   sleep(1);
   (*semaphore)++;
}

/*The thread_f function is defined, which represents the behavior of a philosopher. It takes a pointer to an integer (arg) as input, which represents the philosopher's number. Inside an infinite loop, the philosopher waits for access to the shared resource, checks if it's their turn to eat based on the state, prints their action if it is, updates the state, and then signals that they're done with the shared resource.
*/

void *thread_f(void *arg)
{
   int no = *((int*)arg);
   int st=no;
   while(1)
   {
      wait(&semaphore);
      if(state==st)
      {
         printf("From thread [%d] >> %d\n",st,no);
         no+=2;
         state=3-st;
      }
      signal(&semaphore);
   }
   pthread_exit(NULL);
}

int main()
{
   pthread_t td1,td2;
   int odd=1;
   int even=2;
   pthread_create(&td1,NULL,(void *)thread_f,&odd);
   pthread_create(&td2,NULL,(void *)thread_f,&even);
   pthread_join(td1,NULL);
   pthread_join(td2,NULL);
   return 0;
}
