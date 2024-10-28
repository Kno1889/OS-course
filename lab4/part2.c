#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int amount = 0;
pthread_mutex_t lock;
sem_t deposit_sem; 
sem_t withdraw_sem; 


void *deposit(void *arg) {
    int deposit_amount = *((int*)arg);

    sem_wait(&deposit_sem); // decrement deposit semaphore
    pthread_mutex_lock(&lock); // lock mutex
    
    amount += deposit_amount; // critical section
    printf("Executing deposit function\n");
    printf("Amount after deposit = %d\n", amount);
    
    pthread_mutex_unlock(&lock); // unlock mutex
    sem_post(&withdraw_sem); // increment withdrawal semaphore
    
    pthread_exit(NULL); // exit thread
}


void *withdraw(void *arg) {
    int withdraw_amount = *((int*)arg);

    sem_wait(&withdraw_sem); // decrement withdraw semaphore
    pthread_mutex_lock(&lock); // lock mutex
    
    amount -= withdraw_amount; // critical section
    printf("Executing Withdraw function\n");
    printf("Amount after withdrawal = %d\n", amount);
    
    pthread_mutex_unlock(&lock); // unlock mutex
    sem_post(&deposit_sem); // increment deposit semaphore 
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // initialize mutex lock and semaphores
    pthread_mutex_init(&lock, NULL);
    sem_init(&deposit_sem, 1, 4); // shared, init value = 4
    sem_init(&withdraw_sem, 1, 0); // shared, init value = 0

    // parse command line arguments
    int transaction_amount = atoi(argv[1]);

    // create 7 threads for deposits
    pthread_t deposit_threads[7];
    for (int i = 0; i < 7; ++i) {
        pthread_create(&deposit_threads[i], NULL, deposit, &transaction_amount);
    }

    // create 3 withdraw threads
    pthread_t withdraw_threads[3];
    for (int i = 0; i < 3; ++i) {
        pthread_create(&withdraw_threads[i], NULL, withdraw, &transaction_amount);
    }

    // join all threads
    for (int i = 0; i < 7; ++i) {
        pthread_join(deposit_threads[i], NULL);
    }

    for (int i = 0; i < 3; ++i) {
        pthread_join(withdraw_threads[i], NULL);
    }

    // print final balance, destroy mutex lock & semaphores
    printf("Final balance: %d\n", amount);

    pthread_mutex_destroy(&lock);
    sem_destroy(&deposit_sem);
    sem_destroy(&withdraw_sem);

    return 0;
}
