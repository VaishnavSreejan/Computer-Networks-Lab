#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<arpa/inet.h>

int clients[10],count=0;
void *chat(void *arg){
	int s=*(int *)arg;
	char msg[100];
	int n,i;
	
	while((n=recv(s,msg,sizeof(msg)-1,0))>0){
   	msg[n]='\0';

   	printf("Received: %s",msg);

   	 for(i=0;i<count;i++){
        	if(clients[i]!=s)
           	 send(clients[i],msg,n,0);
    }
}
	close(s);
	return NULL;
}

int main(){
	int s,c;
	struct sockaddr_in server,client;
	socklen_t len=sizeof(client);
	pthread_t t;
	
	s=socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=INADDR_ANY;
	
	bind(s,(struct sockaddr *)&server,sizeof(server));
	listen(s,5);
	
	printf("\nWaiting for clients.......\n");
	
	while(1){
		c=accept(s,NULL,NULL);
		clients[count++]=c;
		pthread_create(&t,NULL,chat,&clients[count-1]);
		pthread_detach(t);
	
		printf("Client connected\n");

	}
	close(s);
	return 0;
}
		










