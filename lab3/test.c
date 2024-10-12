# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>


int main()
{
    pid_t pid, pid_1;

    pid = fork();

    if(pid < 0){
        printf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0){
        pid_1 = getpid();
        printf("child : pid = %d\n", pid);
        printf("child : pid1 = %d\n", pid_1);
    }else{
        pid_1 = getpid();
        printf("parent : pid = %d\n", pid);
        printf("parent : pid1 = %d\n", pid_1);
        wait(NULL);
    }
    return 0;
}
