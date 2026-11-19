#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<time.h>

int main(){
	int s;
	char msg[100]="Time Request";
	struct sockaddr_in server;
	socklen_t len=sizeof(server);
	
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s<0){
		perror("Socket creation failed");
		return 1;
	}
	
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	sendto(s,msg,strlen(msg)+1,0,(struct sockaddr *)&server,len);
	printf("Time Request Sent to server \n");

	recvfrom(s,msg,sizeof(msg),0,(struct sockaddr *)&server,&len);
	printf("Current Time is : %s ", msg);

	close(s);
	return 0;
}


