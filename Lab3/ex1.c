#include <stdio.h>
#include <unistd.h>

int main(){
	printf("real UID=%d, effective UID=%d\n",getuid(),geteuid());
	return 0;
}
