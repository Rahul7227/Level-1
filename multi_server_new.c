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

int cnt=0;

int main()
{

	system("clear");
	//socket - create an endpoint for communication
	int serverfd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(serverfd==-1)
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

	//int opt;
	//setsockopt(serverfd,SOL_SOCKET,REUSEADDR,&opt,sizeof(opt));
	//bind a name to a socket
	int ret=bind(serverfd,(struct sockaddr*)&server, sizeof(server)); 

	if(ret==-1)
	{
		printf("[+]Error in binding \n");
		exit(1);
	}

	//listen for connections on a socket

	//int socketfd;

	listen(serverfd,10);
	//{
	//	printf("[+]listening....\n");
	//	}
	/*	else
		{
		printf("[+}Error binding...\n");
		}*/
	int size=sizeof(struct sockaddr);
	char buf[256];
	
	while(1)
	{
		//accept a connection on a socket
		int clientfd=accept(serverfd,(struct sockaddr*)&client,&size);
		cnt++;

		if(clientfd==-1 )
		{
			exit(1);
		}
		printf("Request accepted from clint=%d\n",clientfd);


		printf("connection accepted from %s : %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

		int pid=fork();
		if(pid==-1)
		{
			printf("for error :");
		}
		if(pid==0)
		{
			close(serverfd);

			for( ; ;)
			{
				int i;
				bzero(buf,sizeof(buf));
				
				read(clientfd,buf,sizeof(buf));

				for(i = 0; buf[i]!='\0';i++)
					if((buf[i]>='a'&&buf[i]<='z')||(buf[i]>='A'&&buf[i]<='Z'))
					{
						buf[i]=buf[i]^32;
					}
					printf("Message received from client %d:%s \t to client:", cnt,buf);
				
					bzero(buf,sizeof(buf));

					int n=0;
					printf("enter msg to server : ");
										
					while((buf[n++]=getchar())!='\n');

					write(clientfd,buf,sizeof(buf));

	
			//	}
				if(strcmp(buf,"exit")==0)
				{
					printf("%s is disconnected from server \n",inet_ntoa(client.sin_addr));
					break;
				}
			}


		}
		else
		{

			close(clientfd);
		}

		
	}	



}








