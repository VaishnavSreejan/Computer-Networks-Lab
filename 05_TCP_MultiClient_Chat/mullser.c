#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>

int c[10],n=0;

void *chat(void *p)
{
    int s=*(int *)p;
    char m[100];

    while(recv(s,m,100,0)>0){
        for(int i=0;i<n;i++){
            if(c[i]!=s){
                send(c[i],m,100,0);
                printf("%s",m);
            }
        }
    }

    close(s);
    return NULL;
}

int main()
{
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in a={AF_INET,htons(8080),INADDR_ANY};

    bind(s,(void*)&a,sizeof(a));
    listen(s,10);

    printf("Server waiting...\n");

    while(n<10)
    {
        c[n]=accept(s,0,0);

        pthread_t t;
        pthread_create(&t,0,chat,&c[n++]);
        pthread_detach(t);
    }

    close(s);
    return 0;
}