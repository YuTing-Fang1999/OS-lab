#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
int main(){
	mqd_t mql=mq_open("/OS",O_WRONLY|O_CREAT,0644,NULL);
	if(mql<0) printf("mql error\n");
	char buffer[1000];
	do{
		memset(buffer,'\0',sizeof(buffer));
		fgets(buffer,1000,stdin);
		int send=mq_send(mql,buffer,strlen(buffer)+1,0);
		if(send<0) printf("send error\n");
	}while(strncmp("exit",buffer,4));
	return 0;
}

