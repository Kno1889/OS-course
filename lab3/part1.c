#include <stdio.h>
#include  <sys/types.h> 

void main()
{
	pid_t pid;	
	printf("%d\n",getpid()); // parent p1
	
    pid = fork();
    
	if(pid == 0) {	
		printf("%d\n",getpid()); //first child, p2

        pid = fork();
        
        if(pid == 0){
            printf("%d\n",getpid()); // p3

            pid = fork();        
            if(pid == 0){
                printf("%d\n",getpid()); // p4
                
                pid = fork();
                
                if(pid == 0) printf("%d\n",getpid()); // p6
                else wait();
            }else{
                wait();
                
                pid = fork();
                
                if(pid == 0) printf("%d\n",getpid()); // p7
                else wait();
            }
        }
        else{
            wait();
            pid = fork();

            if(pid == 0){
                printf("%d\n",getpid()); // p5
                
                pid = fork();
                
                if (pid == 0) printf("%d\n",getpid()); // p8
                else wait();
            }
            else{
                wait();
                pid = fork();
                
                if (pid == 0) printf("%d\n",getpid()); // p9
                else wait();
            }
        }
	}
	else {
        wait();
	}
}
