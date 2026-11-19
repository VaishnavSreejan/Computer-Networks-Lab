#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int s;
    char msg[500],result[1000];
    struct sockaddr_in server;
    socklen_t len=sizeof(server);

    s=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(8080);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    printf("Enter a sentence: ");
    fgets(msg,sizeof(msg),stdin);

    sendto(s,msg,strlen(msg),0,
        (struct sockaddr *)&server,len);

    int n=recvfrom(s,result,sizeof(result)-1,0,
        (struct sockaddr *)&server,&len);

    result[n]='\0';

    printf("\nTranslated sentence: %s\n",result);

    close(s);
    return 0;
}