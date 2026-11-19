#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
	int s,n,i,j;
	long fact;
	struct sockaddr_in server;
	
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s<0){
		perror("Socket Creation Failed");
		return 1;
	}
	
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	

	if(connect(s, (struct sockaddr *)&server,sizeof(server))<0){
		perror("Connection Failed");
		close(s);
		return 1;
	}

	printf("\nConnected to server successfully\n");

	printf("Enter the number to Find Factorial : ");
	scanf("%d",&n);
	write(s,&n,sizeof(n));

	read(s,&fact,sizeof(fact));

	printf("The Factorial of %d is: %ld",n,fact);

	close(s);
	return 0;
}
