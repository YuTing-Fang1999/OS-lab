#include <stdio.h>
#include <unistd.h>

int main(){
	printf("uid=%d,euid=%d\n",getuid(),geteuid());
	FILE* f=fopen("rootFile","a");
	if(f==NULL){
		printf("can not open\n");
		return 0;
	}
	fprintf(f,"uid=%d\n",getuid());
	fprintf(f,"euid=%d\n",geteuid());
	fclose(f);
	return 0;
}
