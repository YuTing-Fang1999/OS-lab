#include <stdio.h>
#include <pthread.h>
int count=0;
void* add(){
	for(int i=0;i<250000000;++i)
		count++;
	pthread_exit(NULL);
}
void* sub(){
	for(int i=0;i<250000000;++i)
		count--;
	pthread_exit(NULL);
}
int main(){
	pthread_t id[4];
	pthread_create(&id[0],NULL,add,NULL);
	pthread_create(&id[1],NULL,add,NULL);
	pthread_create(&id[2],NULL,sub,NULL);
	pthread_create(&id[3],NULL,sub,NULL);

	for(int i=0;i<4;++i)
		pthread_join(id[i],NULL);
	printf("count=%d\n",count);
	pthread_exit(NULL);
	return 0;
}
