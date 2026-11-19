#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
	int s,c,a[10][10],n,i,j;
	int upper=1,lower=1,diagonal=1;
	char result[50];
	struct sockaddr_in server;
	
	s=socket(AF_INET,SOCK_STREAM,0);
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

	if(listen(s,1)<0){
		perror("Listen failed");
		close(s);
		return 1;
	}

	printf("\nWaiting for Client.........\n");
	
	c=accept(s,NULL,NULL);
	if(c<0){
		perror("connection Failed\n");
		close(s);
		return 1;
	}
	printf("\nConnected successfully\n");
	read(c,&n,sizeof(n));
	read(c,a,sizeof(a));

	printf("\n Received Matrix is :\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%d",a[i][j]);
		printf("\n");
	}

	printf("The Matrix Order is : %d",n);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			if(i>j && a[i][j]!=0)
				upper=0;
			if(i<j && a[i][j]!=0)
				lower=0;
			if(i!=j && a[i][j]!=0)
				diagonal=0;
		}

	if(diagonal)
		strcpy(result,"Diagonal Matrix");
	else if(lower)
		strcpy(result,"lower triangular matrix");
	else if(upper)
		strcpy(result,"Upper triangular matrix");
	else
		strcpy(result,"Normal matrix");

	write(c,result,sizeof(result));
	printf("The matrix Type is : %s",result);

	close(c);
	close(s);
	return 0;
}

				

	