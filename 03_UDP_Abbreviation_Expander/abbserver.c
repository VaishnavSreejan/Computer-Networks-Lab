#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
	int s,n,i;
	char msg[100],result[500]="";
	char *abbr[] = {"idk","omg","tbh","ig","lol"};
	char *meaning[] = {"I don't know","OH my God","To be honest","i guess","laughing out loud"};
	struct sockaddr_in server,client;
	socklen_t len=sizeof(client);
	
	s=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_port=htons(9002);
	server.sin_addr.s_addr=INADDR_ANY;
	
	bind(s,(struct sockaddr *)&server,sizeof(server));
	printf("\n Waiting for client....\n");
	
	n=recvfrom(s,msg,sizeof(msg)-1,0,(struct sockaddr *)&client,&len);
	msg[n]='\0';
	
	printf("The Received message is :%s",msg);
	
	char *word=strtok(msg," \n");
	while(word != NULL){
		for(i=0;i<5;i++){
			if(strcmp(word,abbr[i])==0)
				break;
		}
		strcat(result,(i<5)? meaning[i]:word);
		strcat(result," ");
		word=strtok(NULL," \n");
	}
	
	sendto(s,result,strlen(result)+1,0,(struct sockaddr *)&client,len);
	printf("Expanded message is : %s",result);

	close(s);
	return 0;
}
