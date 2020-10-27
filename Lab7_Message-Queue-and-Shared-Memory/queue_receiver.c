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
//	connect queqe
	struct mq_attr attr;
	attr.mq_flags=0;
	attr.mq_maxmsg=10;
	attr.mq_msgsize=MAX_SIZE;
	attr.mq_curmsgs=0;
	mqd_t mql=mq_open(name,O_RDONLY|O_CREAT,0644,&attr);
	
	if(mql==-1){
		perror("mql error:\n");
		exit(1);
	}
	
//	recieve
	char buffer[MAX_SIZE+1];
	do{
//		recieve from queue
		ssize_t bytes_read=mq_receive(mql,buffer,8192,NULL);
		if(bytes_read<0){
			perror("bytes_read error\n");
			exit(1);
		}
		
		buffer[bytes_read]='\0';
		printf("received:%s",buffer);
		
	}while(strncmp(buffer,"exit\n",5));
	
//	close queqe
	int s_close=mq_close(mql);
	if(s_close==-1){
		perror("s_close error:\n");
		exit(1);
	}
//	unlink queqe
	int tmp=mq_unlink(name);
	if(tmp==-1){
		exit(0);
	}
	return 0;
}
