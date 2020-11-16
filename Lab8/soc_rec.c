#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
	struct sockaddr_in address,client_address;

	int sock=socket(PF_INET,SOCK_DGRAM,0);
	if(sock<0) printf("create error\n");

	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	address.sin_port=htons(5555);
	address.sin_addr.s_addr=INADDR_ANY;

	if(bind(sock,(struct sockaddr*)&address,sizeof(address))==-1) printf("error bind\n");

	int addr_len=sizeof(address);
	int client_addr_len;
	char buffer[50];
	for(;;){
		int byte_recv=recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr*)&client_address,&client_addr_len);
		if(byte_recv<0) printf("error recv\n");
	
		printf("data: %s\n",buffer);
	}
	close(sock);
	return 0;
}
