#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>

int c[10],n=0;

void *chat(void *p)
{
    int s=*(int *)p;
    char m[100];
    int k;

    while((k=recv(s,m,99,0))>0)
    {
        m[k]='\0';
        printf("Message: %s",m);

        for(int i=0;i<n;i++)
            if(c[i]!=s)
                send(c[i],m,k,0);
    }

    close(s);
    return NULL;
}

int main()
{
    int s;
    struct sockaddr_in a={AF_INET,htons(8080),INADDR_ANY};

    s=socket(AF_INET,SOCK_STREAM,0);
    bind(s,(void*)&a,sizeof(a));
    listen(s,10);

    printf("Server waiting...\n");

    while(n<10)
    {
        c[n]=accept(s,0,0);
        printf("Client %d connected\n",n+1);

        pthread_t t;
        pthread_create(&t,0,chat,&c[n]);
        pthread_detach(t);
        n++;
    }

    close(s);
    return 0;
}