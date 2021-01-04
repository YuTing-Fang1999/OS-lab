#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
int count=0;
sem_t* mutex;
void* add(){
	for(int i=0;i<1000000;++i){
		sem_wait(mutex);
		count++;
		sem_post(mutex);
	}
	pthread_exit(NULL);
}
void* sub(){
	for(int i=0;i<1000000;++i){
		sem_wait(mutex);
		count--;
		sem_post(mutex);
	}
	pthread_exit(NULL);
}
int main(){
	mutex = sem_open("/mysem",O_CREAT,S_IRUSR|S_IWUSR,1);
	pthread_t id[4];
	pthread_create(&id[0],NULL,add,NULL);
	pthread_create(&id[1],NULL,add,NULL);
	pthread_create(&id[2],NULL,sub,NULL);
	pthread_create(&id[3],NULL,sub,NULL);

	for(int i=0;i<4;++i)
		pthread_join(id[i],NULL);
	printf("count=%d\n",count);
	sem_close(mutex);
	sem_unlink("/mysem");
	pthread_exit(NULL);
	return 0;
}
