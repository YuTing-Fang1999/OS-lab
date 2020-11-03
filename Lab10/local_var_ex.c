#include <stdio.h>
#include <pthread.h>

static __thread int glob=0;
void *incr(void* arg){
	int loop=*(int*)arg;
	for(int i=0;i<loop;++i){
		++glob;
	}
	printf("tid=%lu, glob=%d\n",pthread_self(),glob);
	pthread_exit(NULL);
}

int main(){
	printf("glob value before run 2 thread: %d\n",glob);
	int loop1=50,loop2=100;
	pthread_t id[2];
	pthread_create(&id[0],NULL,incr,&loop1);
	pthread_create(&id[1],NULL,incr,&loop2);

	pthread_join(id[0],NULL);
	pthread_join(id[1],NULL);

	printf("glob value after run 2 thread: %d\n",glob);
	return 0;
}
