#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; // shared by threads
void *runner (void *param); // threads call this function



int main(int argc, char *argv[])
{
    pthread_t tid; // thread id
    pthread_attr_t attr; // set of thread attributes

    // set default attributes of the thread
    pthread_attr_init(&attr);

    //create thread
    pthread_create(&tid, &attr, runner, argv[1]);

    //wait for thread to exit
    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);
}

// the thread will execute in this function

void *runner(void *param)
{
    int i, upper = atoi(param);
    sum = 0;
    
    for (i = 1; i <= upper; i++)
        sum += i;
    
    pthread_exit(0);
}