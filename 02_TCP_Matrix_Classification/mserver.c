#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
	int s,n,c,a[10][10],i,j;
	char result[50];
	int upper=1,lower=1,diagonal=1;
	struct sockaddr_in server;

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s<0){
		perror("Socket creation failed");
		return 1;
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=INADDR_ANY;
	
	bind(s,(struct sockaddr *)&server,sizeof(server));

	
	if(listen(s,1)<0){
		perror("Listen Failed");
		close(s);
		return 1;
	}
	
	printf("Waiting for Client......\n");
	
	c=accept(s,NULL,NULL);
	if(c<0){
		perror("Connection Failed");
		close(s);
		return 1;
	}
	printf("Connected Successfully\n");
	
	read(c,&n,sizeof(n));
	read(c,a,sizeof(int)*n*n);
	
	printf("Received Matrix is :\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d",a[i][j]);
		}
		printf("\n");
	}
	printf("The Matrix Order is : %d",n);
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i>j && a[i][j]!=0)
				upper=0;
			if(i<j && a[i][j]!=0)
				lower=0;
			if(i != j && a[i][j]!=0)
				diagonal=0;
		}
	}

	if(diagonal)
		strcpy(result,"Diagonal Matrix");
	else if(upper)
		strcpy(result,"Upper Triangular Matrix");
	else if(lower)
		strcpy(result,"Lower Triangular Martix");
	else
		strcpy(result,"Normal Matrix");
	
	write(c,result,sizeof(result));
	printf("The Matrix order is : %s",result);
	
	close(c);
	close(s);
	return 0;
}

	


