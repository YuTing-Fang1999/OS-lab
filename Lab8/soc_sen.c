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
	address.sin_port=htons(5555);
	address.sin_addr.s_addr=inet_addr("10.0.2.15");

	int addr_len=sizeof(address);
	char buffer[3]="hi\0";
	int byte_sent=sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr*)&address,addr_len);
	if(byte_sent<0) printf("error send\n");

	close(sock);
	return 0;
}
