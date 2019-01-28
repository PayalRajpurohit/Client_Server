#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    
#include<pthread.h> 
#include<sys/types.h>
#include<netinet/in.h>


int requester(int port)
{
	int sock;
	struct sockaddr_in server;
	int ch;
	char c_message[2000];
	char message[100];
	
	
		//Create socket
			sock = socket(AF_INET , SOCK_STREAM , 0);
			if (sock == -1)
			{
    			printf("Could not create socket");
			}
			puts("Socket created");
	 
			server.sin_addr.s_addr = inet_addr("127.0.0.1");
			server.sin_family = AF_INET;
			server.sin_port = htons(port);
			//Connect to remote server
			if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
			{
    			perror("connect failed. Error");
			}

			puts("Connected\n");
	
			if(port==8888)
				{
					printf("\nEnter the service number\n");
					scanf("%s",message);
			   		send(sock, message, strlen(message), 0);
			    	//Receive a reply from the server
			    	recv(sock ,c_message , 2000 , 0);
			    	printf("Reply from Server :");
			    	printf(c_message);
			    	if(strcmp(c_message,"YES")==0)
			    		return 1;
				}
				else
				{
					printf("Can you provide %d service \n",port );
					sprintf(message,"%ld", port);
					write(sock , message , strlen(message));
					recv(sock ,c_message , 2000 , 0);
					printf(c_message);
				}
			
			
	return 0;
}

  int main(int c, char *argv[])
{ 
	int port;
	printf("Enter port number\n");
	scanf("%d",&port);
	int n=requester(port);
	//printf("%d\n",n);
	if(n==0){
	printf("\nEnter port number\n");
	scanf("%d",&port);
	requester(port);
  	}
  	
  	return 0;
}
