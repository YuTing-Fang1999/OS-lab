#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){
	int shm_fd=shm_open("OS",O_CREAT|O_RDWR,0666);
	if(shm_fd<0) printf("open error\n");
	ftruncate(shm_fd,1024);
	int* data=mmap(0,1024,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
	if(data==MAP_FAILED){
		printf("shm_base fail\n");
	}
	//char buffer[1024];
	//fgets(buffer,sizeof(buffer),stdin);
	for(int i=0;i<4;++i){
		data[i]=i;
	}	
	return 0;
}
