#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<time.h>

int main(){
	
	int s;
	char msg[100]="Time Request";
	struct sockaddr_in server;
	socklen_t len;
	
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s<0){
		perror("Socket creation Failed");
		return 1;
	}
	
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	len=sizeof(server);

	sendto(s,msg,strlen(msg)+1,0,(struct sockaddr *)&server,len);
	printf("\nTime Request send to server \n");

	recvfrom(s,msg,sizeof(msg),0,(struct sockaddr *)&server,&len);
	printf("\nCurrent time is : %s",msg);

	close(s);
	return 0;
}
