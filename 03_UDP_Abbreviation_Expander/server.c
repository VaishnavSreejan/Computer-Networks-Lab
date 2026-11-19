#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int s;
    char msg[500];
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);

    s=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(8080);
    server.sin_addr.s_addr=INADDR_ANY;

    bind(s,(struct sockaddr *)&server,sizeof(server));

    printf("Waiting for client...\n");

    recvfrom(s,msg,sizeof(msg)-1,0,
        (struct sockaddr *)&client,&len);

    msg[sizeof(msg)-1]='\0';

    char *abbr[]={"tbh","ig","tbf","atm","irl",
                  "lol","asap","omg","ttyl","idk","nvm"};

    char *meaning[]={"to be honest","I guess","to be fair",
                     "at the moment","in real life",
                     "laughing out loud","as soon as possible",
                     "oh my god","talk to you later",
                     "I don't know","never mind"};

    char result[1000]="";
    char *word=strtok(msg," ,.!?\n");

    while(word!=NULL)
    {
        int found=0;

        for(int i=0;i<11;i++)
        {
            if(strcmp(word,abbr[i])==0)
            {
                strcat(result,meaning[i]);
                found=1;
                break;
            }
        }

        if(!found)
            strcat(result,word);

        strcat(result," ");
        word=strtok(NULL," ,.!?\n");
    }

    sendto(s,result,strlen(result),0,
        (struct sockaddr *)&client,len);

    close(s);
    return 0;
}