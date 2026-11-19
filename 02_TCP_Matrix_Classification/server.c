#include<stdio.h>
#include<unistd.h>
#include <arpa/inet.h>
#include<string.h>

int main(){

    int s,c,n,a[10][10],i,j;
    int upper=1,lower=1,diagonal=1;
    char result[50];
    struct sockaddr_in server;

    s=socket(AF_INET,SOCK_STREAM,0);
    if(s<0){
        perror("Socket Connection Failed \n");
        return 1;
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(8080);
    server.sin_addr.s_addr=INADDR_ANY;

    if(bind(s, (struct sockaddr *)&server, sizeof(server))<0){
        perror("Bind connection failed");
        close(s);
        return 1;
    }

    if(listen(s,1)<0){
        perror("Listen failed\n");
        close(s);
        return 1;
    }

    c=accept(s,NULL,NULL);
    if(c<0){
        perror("Connection failed\n");
        close(s);
        return 1;
    }

    printf("Client Connected Successfully");
    read(c,&n,sizeof(n));
    read(c,a,sizeof(a));

    printf("Received Matrix is :\n");
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
    
    else if(upper)
        strcpy(result,"Upper Triangular Matrix");
    
    else if(lower)
        strcpy(result,"Lower Triangular Matrix");
    
    else
        strcpy(result,"Normal Matrix");

    write(c,result,sizeof(result));
    printf("The Matrix Type is: %s",result);

    close(c);
    close(s);
    return 0;
}