#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //ftruncate
int main(){
	int shm_fd=shm_open("os",O_CREAT|O_RDWR,0666);
	ftruncate(shm_fd,1024);
	char *shm_base=mmap(0,1024,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);

	char buffer[1024];
	fgets(buffer,sizeof(buffer),stdin);

	char *ptr=shm_base;
	ptr+=sprintf(ptr,"%s",buffer);

	return 0;

}
