#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int glob=10;
int main(){
	int local=10;
	if(fork()==0){
		++glob;
		++local;
		printf("child:pid=%d,glob= %d,local=%d\n",getpid(),glob,local);
	}
	else{
	//	wait(NULL);
		printf("parent:pid=%d,glob= %d,local=%d\n",getpid(),glob,local);
	}
	return 0;
}
