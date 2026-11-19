#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
	int s,n;
	char msg[100],result[500];
	struct sockaddr_in server;
	socklen_t len=sizeof(server);
	
	s=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_port=htons(9002);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	printf("Enter the sentence : ");
	fgets(msg,sizeof(msg),stdin);
	
	sendto(s,msg,strlen(msg),0,(struct sockaddr *)&server,len);
	
	n=recvfrom(s,result,sizeof(result)-1,0,(struct sockaddr *)&server,&len);
	result[n]='\0';

	printf("Expended Message is : %s ",result);
	
	close(s);
	return 0;
}
