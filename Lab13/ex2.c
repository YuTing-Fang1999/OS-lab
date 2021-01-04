#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mtx;
pthread_cond_t cond1;
pthread_cond_t cond2;
void *print1(){
	while(1){
		pthread_mutex_lock(&mtx);
		printf("enter p1\n");
		pthread_cond_wait(&cond1,&mtx);
		printf("%d\n",1);
		pthread_mutex_unlock(&mtx);
		printf("outer p1\n");
		sleep(1);
		pthread_cond_signal(&cond2);
		printf("cond2\n");
	}
}
void *print2(){
	while(1){
		pthread_mutex_lock(&mtx);
		printf("enter p2\n");
		pthread_cond_wait(&cond2,&mtx);
		printf("%d\n",2);
		pthread_mutex_unlock(&mtx);
		printf("outer p2\n");
		sleep(1);
		pthread_cond_signal(&cond1);
		printf("cond1\n");
	}
}
int main(){
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&cond1,NULL);
	pthread_cond_init(&cond2,NULL);

	pthread_t id[2];
	pthread_create(&id[0],NULL,print1,NULL);
	sleep(1);
	pthread_create(&id[1],NULL,print2,NULL);
	
	pthread_cond_signal(&cond1);

	pthread_join(id[0],NULL);
	pthread_join(id[1],NULL);

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond2);
	return 0;
}
