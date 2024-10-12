#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; // shared by threads
#define SIZE 30

typedef struct { 
    int from_index;
    int to_index;
} parameters;

void *runner (parameters *param); // threads call this function

int numbers[SIZE];

void add_numbers(){
    for(int i = 0; i < 30; i++)
        numbers[i] = i + 1;
}

int main()
{
    add_numbers();
    parameters *data1 = (parameters *) malloc (sizeof(parameters));
    data1->from_index = 0; data1->to_index = (SIZE/2) - 1;

    parameters *data2 = (parameters *) malloc (sizeof(parameters));
    data2->from_index = (SIZE / 2); data2->to_index = SIZE - 1;
    
    pthread_t tid1; // thread 1 id
    pthread_t tid2; // thread 1 id
    pthread_attr_t attr1; // set of thread attributes
    pthread_attr_t attr2; // set of thread attributes

    // set default attributes of the thread
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    //create thread
    pthread_create(&tid1, &attr1, runner, data1);
    pthread_create(&tid2, &attr2, runner, data2);

    //wait for thread to exit
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("sum = %d\n", sum);
}

// the thread will execute in this function

void *runner(parameters *param)
{
    // add numbers elements from from_index to to_index
    for (int i = param->from_index; i <= param -> to_index; i++)
        sum += numbers[i];
    
    pthread_exit(0); // terminate thread and return
}