#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>

int s;

void *receive(void *p)
{
    char m[100];
    int n;

    while((n=recv(s,m,99,0))>0)
    {
        m[n]='\0';
        printf("%s",m);
    }

    return NULL;
}

int main()
{
    struct sockaddr_in a={AF_INET,htons(8080)};
    a.sin_addr.s_addr=inet_addr("127.0.0.1");

    s=socket(AF_INET,SOCK_STREAM,0);
    connect(s,(void*)&a,sizeof(a));

    pthread_t t;
    pthread_create(&t,0,receive,0);

    char m[100];

    while(fgets(m,100,stdin))
        send(s,m,strlen(m),0);

    close(s);
    return 0;
}