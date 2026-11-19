#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <arpa/inet.h>

int main(){

    int s,c,n,a[10][10],i,j;
    char result[50];
    struct sockaddr_in server;

    s=socket(AF_INET,SOCK_STREAM,0);
    if(s<0){
        perror("Socket Connection Failed\n");
        return 1;
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(8080);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(s,(struct sockaddr *)&server,sizeof(server))<0){
        perror("Connection Failed\n");
        close(s);
        return 1;
    }

    printf("Connected Successfully");
    printf("Enter the order of the matrix \n");
    scanf("%d",&n);

    printf("Enter the elements of the matrix : \n");
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&a[i][j]);

    write(s,&n,sizeof(n));
    write(s,a,sizeof(a));

    read(s,result,sizeof(result));

    printf("The Matrix Type is : %s",result);

    close(s);
    return 0; 
}