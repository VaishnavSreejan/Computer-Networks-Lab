#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
	int s,c,n,i,j;
	long fact;
	struct sockaddr_in server;

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s<0){
		perror("Socket Creation Failed ");
		return 1;
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=INADDR_ANY;

	if(bind(s, (struct sockaddr *)&server,sizeof(server))<0){
		perror("Bind Failed");
		close(s);
		return 1;
	}
	
	listen(s,1);
	printf("Waiting for client........\n");
	
	c=accept(s,NULL,NULL);
	if(c<0){
		perror("Connection Failed \n");
		close(s);
		return 1;
	}

	printf("Connected Successfully\n");
	read(c,&n,sizeof(n));
	
	printf("The Received number is : %d",n);
	fact=1;		
	for(i=1;i<=n;i++){
		fact=fact*i;
	}
	write(c,&fact,sizeof(fact));

	printf("\nthe factorial of %d is : %ld \n",n,fact);
	printf("\nThe factorial is sended to the client \n");


	close(c);
	close(s);
	return 0;
}



	
	