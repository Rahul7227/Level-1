#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/ip.h>
#include<netinet/in.h> //used in sin_family,sin_port,sin_addr
#include<arpa/inet.h> //the available the types in_port_t and type in_addr_t as defined

#define PORT 5000

int main()
{

 	system("clear");
	//socket - create an endpoint for communication
	int clientfd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if(clientfd==-1)
	{
		printf("[+]Error in connection \n");
		exit(1);
	}

	printf("[+]server socket created sucessfully\n");
	
	struct sockaddr_in server,client;

	memset(&server,'\0',sizeof(server));
	
	server.sin_family=AF_INET;
	
	//htons is convert values between host and network byte order
	server.sin_port=htons(PORT);

	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	   
	//connect a name to a socket
	
	int c=connect(clientfd,(struct sockaddr*)&server,sizeof(server));
	if(c==-1)
	{
		printf("[+]Error in connecting \n");
		exit(1);
	}

	//printf("[+]bind to the port number %d\n",4444);
	printf("connected to server\n");

	char buf[256];
	while(1)
	{
		bzero(buf,sizeof(buf));
		printf("enter msg to server : ");
		//gets(snd);
		int n=0;
		//scanf("%s[^\n]s",snd);

		while((buf[n++]=getchar())!='\n');
		
		write(clientfd,buf,sizeof(buf));
		//for(;;)
               // {
               // int r=recv(clientfd,rcv,256,0);
               // rcv[r]='\0';
		//printf("rec the messege :%s\n",rcv);
                //}
		//read(recv(clientfd,buf,sizeof(buf),0)<0)
		//bzero(buf,sizeof(buf));
		if(recv(clientfd,buf,256,0)<0)
		{
			printf("[+]error receving data\n");
		}
		else
		{
			printf("server : \t%s\n",buf);
		}
		//bzero(buf,sizeof(buf));
		//if(strcmp(write,"exit")==0)
		//break;
	}
//	close(clientfd);
}

	
	
	


		
	
	



