#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
void *child(void *arg){
	int *input = (int*) arg;
	sleep(3);
	int *result = malloc(sizeof(int)*1);
	result[0] = input[0]+input[1];
	pthread_exit((void*)result);
}
int main(){
	int input[2]={1,2};
	pthread_t t;
	pthread_create(&t,NULL,child,input);

	void* ret;
	pthread_join(t,&ret);


	printf("%d + %d = %d\n",input[0],input[1],*(int*)ret);
	
	free(ret);

	return 0;
}
