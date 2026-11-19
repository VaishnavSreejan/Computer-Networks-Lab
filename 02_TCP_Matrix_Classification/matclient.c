#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){

	int s,n,a[10][10],i,j;
	char result[50];
	struct sockaddr_in server;
	
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s<0){
		perror("Socket Creation Failed\n");
		return 1;
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(s, (struct sockaddr *)&server,sizeof(server))<0){
		perror("Connection failed");
		close(s);
		return 1;
	}
	printf("Client connected To server successfully \n");

	printf("Enter the order of the matrix :");
	scanf("%d",&n);
	printf("enter the elements of the matrix :\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	}

	write(s,&n,sizeof(n));
	write(s,a,sizeof(a));

	read(s,result,sizeof(result));

	printf("The Matrix Type is : %s",result);
	
	close(s);
	return 0;
}
