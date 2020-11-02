#include <stdio.h>
#include <pthread.h>

static __thread int glob=0;

void *func(){
	glob++;
	printf("tid=%lu,glob=%d\n",pthread_self(),glob);
	pthread_exit(NULL);
}

int main(){
	pthread_t id[2];
	pthread_create(&id[0],NULL,func,NULL);
	pthread_create(&id[1],NULL,func,NULL);

	pthread_join(id[0],NULL);
	pthread_join(id[1],NULL);

	return 0;
}
