#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int* result;
void *child(void *arg){
	int *input = (int*) arg;
	result = malloc(sizeof(int)*1);
	result[0] = input[0]+input[1];

	int i=1;
	while(1){
		printf("sleep %d\n",i);
		sleep(1);
		++i;
	}

	pthread_exit((void*)result);
}
int main(){
	int input[2]={1,2};
	pthread_t t;
	pthread_create(&t,NULL,child,input);
	sleep(1);
	if(pthread_cancel(t)==0){
		printf("cancel thread successfully\n");
	}

	pthread_join(t,NULL);


	printf("%d + %d = %d\n",input[0],input[1],result[0]);
	

	return 0;
}
