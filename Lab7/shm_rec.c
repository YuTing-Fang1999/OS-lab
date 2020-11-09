#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){
	int shm_fd=shm_open("OS",O_RDONLY,0666);
	if(shm_fd<0) printf("open error\n");
	int* data=(int*)mmap(0,1024,PROT_READ,MAP_SHARED,shm_fd,0);
	if(data==MAP_FAILED){
		printf("shm_base fail\n");
	}
	for(int i=0;i<4;++i){
		printf("%d\n",data[i]);
	}

	return 0;
}
