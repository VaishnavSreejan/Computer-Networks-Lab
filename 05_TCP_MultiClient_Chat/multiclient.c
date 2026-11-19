#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<arpa/inet.h>

int s;
void *receive_msg(void *arg){
	int n;
	char msg[100];
	
	while((n=recv(s,msg,sizeof(msg)-1,0))>0){
		msg[n]='\0';
		printf("Received : %s",msg);
	}
	return NULL;
}

int main(){
	
	struct sockaddr_in server;
	pthread_t t;
	char msg[100];
	
	s=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(s,(struct sockaddr *)&server,sizeof(server));
	printf("\nConnected to server\n");

	pthread_create(&t,NULL,receive_msg,NULL);
	
	while(1){
	
		fgets(msg,sizeof(msg),stdin);
		if(strncmp(msg,"exit\n",4)==0)
			break;
		send(s,msg,strlen(msg),0);
	}
	close(s);
	return 0;
}
