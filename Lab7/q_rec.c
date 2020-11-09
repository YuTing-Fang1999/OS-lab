#include <stdio.h>
#include <string.h>
#include <mqueue.h>

int main(){
	struct mq_attr attr;
	attr.mq_flags=0;
	attr.mq_maxmsg=10;
	attr.mq_msgsize=1000;
	attr.mq_curmsgs=0;

	mqd_t mql=mq_open("/OS",O_RDONLY|O_CREAT,0644,&attr);
	if(mql==-1) printf("create error\n");
	char buffer[1001];
	do{
		ssize_t bytes=mq_receive(mql,buffer,8192,NULL);
		if(bytes<0) printf("rec error\n");
		buffer[bytes]='\0';
		printf("receive:%s",buffer);
	}while(strncmp("exit",buffer,4));

	return 0;
}
