#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(){
	int s,n,i,j,a[10][10],type;
	char result[50];
	struct sockaddr_in server;
	
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s<0){
		perror("Socket Creation Failed");
		return 1;
	}
	
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	connect(s,(struct sockaddr *)&server,sizeof(server));

	printf("Connected to server successfully\n");
	
	printf("Enter the Order of the Matrix:\n");
	scanf("%d",&n);
	
	srand(time(NULL));
	type=rand() % 4;

	printf("Generated matrix is :\n");
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(type==0){
				if(i==j)
					a[i][j]=rand()%50+1;
				else
					a[i][j]=0;
			}
			else if(type==1){
				if(i<j || i==j)
					a[i][j]=rand()%50+1;
				else
					a[i][j]=0;
			}
			else if(type==2){
				if(i>j || i==j)
					a[i][j]=rand()%50+1;
				else
					a[i][j]=0;
			}
			else{
				a[i][j]=rand()%50+1;
			}
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}

	write(s,&n,sizeof(n));
	write(s,a,sizeof(int)*n*n);
	
	read(s,result,sizeof(result));
	printf("The Matrix Type is : %s",result);
	
	close(s);
	return 0;
}

	
	