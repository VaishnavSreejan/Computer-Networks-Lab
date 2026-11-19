#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<time.h>

int main(){

	int s;
	char msg[100];
	struct sockaddr_in server,client;
	socklen_t len;

	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s<0){
		perror("Socket creation Failed ");
		return 1;
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=INADDR_ANY;

	if(bind(s,(struct sockaddr *)&server,sizeof(server))<0){
		perror("Bind Failed");
		close(s);
		return 1;
	}

	printf("waiting of client......\n");
	len=sizeof(client);

	recvfrom(s,msg,sizeof(msg),0,(struct sockaddr *)&client,&len);
	printf("\nClient Request Received \n");
	time_t t;
	time(&t);
	strcpy(msg,ctime(&t));

	sendto(s,msg,strlen(msg)+1,0,(struct sockaddr *)&client,len);
	printf("\nTime sended to the client \n");
	
	close(s);
	return 0;
}

	