#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <mqueue.h>
#define name "/q2uqe"
#define MAX_SIZE 1000
int main(){
	/* open the queue */
	mqd_t mql=mq_open(name,O_WRONLY|O_CREAT,0644,NULL);
	if(mql==-1){
		perror("mql error:\n");
		exit(0);
	}
	
//	send
	char buffer[MAX_SIZE];
	printf("send to receiver:\n");
	do{
//		clear buffer
		memset(buffer,'\0',sizeof(buffer));
//		input buffer
		printf(">");
		fgets(buffer,MAX_SIZE,stdin);
//		send to mq
		int send=mq_send(mql,buffer,strlen(buffer)+1,0);
		if(send<0){
			perror("message:\n");
			exit(1);
		}
		
	}while(strncmp(buffer,"exit\n",5));

	return 0;
}
