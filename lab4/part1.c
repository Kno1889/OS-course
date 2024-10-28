#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int amount = 0; 
pthread_mutex_t lock; 

void *deposit(void *arg) {
    int deposit_amount = *((int*)arg);

    pthread_mutex_lock(&lock); // lock

    amount += deposit_amount; // critical section
    printf("Deposit amount: %d\n", amount);
 
    pthread_mutex_unlock(&lock); // unlock

    pthread_exit(NULL); // thread complete
}

void *withdraw(void *arg) {
    int withdraw_amount = *((int*)arg);

    pthread_mutex_lock(&lock); // lock

    amount -= withdraw_amount; // critical section
    printf("Withdrawal amount: %d\n", amount);

    pthread_mutex_unlock(&lock); // unlock

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // parse command line arguments
    int deposit_amount = atoi(argv[1]);
    int withdraw_amount = atoi(argv[2]);

    // create 3 widthraw threads
    pthread_t withdraw_threads[3];
    for (int i = 0; i < 3; ++i) {
        pthread_create(&withdraw_threads[i], NULL, withdraw, &withdraw_amount);
    }

    // create 3 deposit threads
    pthread_t deposit_threads[3];
    for (int i = 0; i < 3; ++i) {
        pthread_create(&deposit_threads[i], NULL, deposit, &deposit_amount);
    }

    // join all threads
    for (int i = 0; i < 3; ++i) {
        pthread_join(withdraw_threads[i], NULL);
        pthread_join(deposit_threads[i], NULL);
    }

    // print final result
    printf("Final balance: %d\n", amount);

    // destroy mutex lock as no longer needed
    pthread_mutex_destroy(&lock);

    return 0;
}
