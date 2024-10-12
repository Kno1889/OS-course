#include <stdio.h>
#include  <sys/types.h> /* This header file has the definition for pid_t type*/

int main()
{
	pid_t pid;	
	printf("%d\n",getpid());
    
	pid = fork();
	if(pid == 0) {	
		printf("%d\n",getpid());
        pid = fork();
        if(pid == 0){
            printf("%d\n",getpid());
            pid = fork();
            if(pid == 0){
                printf("%d\n",getpid());
                pid = fork();
                if(pid == 0){
                    printf("%d\n",getpid());
                }else{
                    wait();
                }
            }
            else{
                wait();
                pid = fork();
                if(pid == 0){
                    printf("%d\n",getpid());
                }
                else {wait();}
            }
        }
        else{
            wait();
            pid = fork();
            if(pid == 0){
                printf("%d\n",getpid());
                pid = fork();
                if (pid == 0){
                    printf("%d\n",getpid());
                }
                else{wait();}
            }
            else{
                wait();
                pid = fork();
                if (pid == 0){
                    printf("%d\n",getpid());
                }
                else {wait();}
            }
        }
	}
	else {
        wait();
	}
}
