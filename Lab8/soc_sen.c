#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
	struct sockaddr_in address;
	int sock=socket(PF_INET,SOCK_DGRAM,0);
	if(sock<0) printf("create error\n");

	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	address.sin_port=htons();
	address.sin_addr.s_addr();
