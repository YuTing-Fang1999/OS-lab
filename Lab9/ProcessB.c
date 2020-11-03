#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <mqueue.h>
#define name "/q2uqe"
#define name2 "/q2uqe2"
#define MAX_SIZE 1000

#include <pthread.h>

void *send(){
	/* open the queue */
	mqd_t mql=mq_open(name,O_WRONLY|O_CREAT,0644,NULL);
	if(mql==-1){
		perror("mql error:\n");
		exit(0);
	}
	
//	send
	char buffer[MAX_SIZE];
	do{
//		clear buffer
		memset(buffer,'\0',sizeof(buffer));
//		input buffer
		printf("send to receiver:");
		fgets(buffer,MAX_SIZE,stdin);
//		send to mq
		int send=mq_send(mql,buffer,strlen(buffer)+1,0);
		if(send<0){
			perror("message:\n");
			exit(1);
		}
		
	}while(strncmp(buffer,"exit\n",5));
}

void *receive(){
//	connect queqe
	struct mq_attr attr;
	attr.mq_flags=0;
	attr.mq_maxmsg=10;
	attr.mq_msgsize=MAX_SIZE;
	attr.mq_curmsgs=0;
	mqd_t mql=mq_open(name2,O_RDONLY|O_CREAT,0644,&attr);
	
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
}

int main(){
	pthread_t thread0,thread1;
	int rc0, rc1;
	rc0 = pthread_create(&thread0,NULL,send,(void *)1);
	rc1 = pthread_create(&thread1,NULL,receive,(void *)2);
	rc0 = pthread_join(thread0,NULL);
	rc1 = pthread_join(thread1,NULL);
	
	return 0;
}
