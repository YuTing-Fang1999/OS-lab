#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int glob=0;
pthread_mutex_t mtx;

void* add(void *arg){
	int loops=*(int*)arg;
	int loc;
	for(int i=0;i<loops;++i){
		pthread_mutex_lock(&mtx);
		loc=glob;
		loc+=2;
		glob=loc;
		pthread_mutex_unlock(&mtx);
	}
}
void* sub(void *arg){
	int loops=*(int*)arg;
	int loc;
	for(int i=0;i<loops;++i){
		pthread_mutex_lock(&mtx);
		loc=glob;
		loc-=2;
		glob=loc;
		pthread_mutex_unlock(&mtx);
	}
}
int main(int argc,char *argv[]){
	pthread_mutex_init(&mtx,NULL);
	int loops=atoi(argv[1]);
	pthread_t id[3];

	pthread_create(&id[0],NULL,add,&loops);
	pthread_create(&id[1],NULL,add,&loops);
	pthread_create(&id[2],NULL,sub,&loops);

	for(int i=0;i<3;++i)
		pthread_join(id[i],NULL);

	printf("glob=%d\n",glob);
	pthread_mutex_destroy(&mtx);
	return 0;
}
