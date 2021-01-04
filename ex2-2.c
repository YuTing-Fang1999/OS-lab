#include <stdio.h>
#include <pthread.h>

int glob=1;
pthread_cond_t cond[3];
pthread_mutex_t mtx;

void* print1(){
	while(1){
	if(glob==1){
		printf("%d ",glob);
		glob=3;
		pthread_cond_signal(&cond[1]);
	}else{
		pthread_cond_wait(&cond[0],&mtx);

	}
	}
}
void* print3(){
	while(1){
	if(glob==3){
		printf("%d ",glob);
		glob=5;
		pthread_cond_signal(&cond[2]);
	}else{
		pthread_cond_wait(&cond[1],&mtx);
	}
	}
}
void* print5(){
	while(1){
	if(glob==5){
		printf("%d ",glob);
		glob=1;
		pthread_cond_signal(&cond[0]);
	}else{
		pthread_cond_wait(&cond[2],&mtx);
	}
	}
}
int main(){
	pthread_cond_init(&cond[0],NULL);
	pthread_cond_init(&cond[1],NULL);
	pthread_cond_init(&cond[2],NULL);
	pthread_mutex_init(&mtx,NULL);

	pthread_t id[3];
	pthread_create(&id[0],NULL,print1,NULL);
	pthread_create(&id[1],NULL,print3,NULL);
	pthread_create(&id[2],NULL,print5,NULL);

	for(int i=0;i<3;++i)
		pthread_join(id[i],NULL);

	return 0;
}

