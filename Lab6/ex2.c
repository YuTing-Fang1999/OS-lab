#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
	if(fork()==0){
		if(fork()==0){
			printf("C ppid=%d,pid=%d\n",getppid(),getpid());
		}else{
			wait(NULL);
			printf("B ppid=%d,pid=%d\n",getppid(),getpid());
		}
	}else{
		wait(NULL);
		if(fork()==0){
			printf("D ppid=%d,pid=%d\n",getppid(),getpid());
		}else{
			wait(NULL);
			if(fork()==0){
				printf("E ppid=%d,pid=%d\n",getppid(),getpid());
			}else{
				wait(NULL);
				printf("A ppid=%d,pid=%d\n",getppid(),getpid());
			}
		}
	}

	return 0;
}	
