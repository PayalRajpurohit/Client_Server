#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int port;
	printf("ENTER A PORT\n");
	scanf("%d",&port);

	int sock, new_sock;
	struct sockaddr_in address;
	int ch;

	int addrlen = sizeof(address);
	char message[1024];
      
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
    	perror("socket failed");
    	exit(EXIT_FAILURE);
	}
    
    printf("Socket Created Successfully !! \n");
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
 	 
	if (bind(sock, (struct sockaddr *)&address, sizeof(address))<0)
	{
    	perror("bind failed");
    	exit(EXIT_FAILURE);
	}
    
	if (listen(sock, 3) < 0)
	{
    	perror("listen failed..");
    	exit(EXIT_FAILURE);
	}
    
    printf("Server is waiting for client to connect..\n");
    	
 
	if ((new_sock = accept(sock, (struct sockaddr*)&address, (socklen_t*) &addrlen)) <0)
	{
    	perror("accept error..");
    	exit(EXIT_FAILURE);
	}

    printf("Connection establised !! \n");
	
	read(new_sock, message, 1024, 0);  							
   	printf("Service requested by Client :\t  %s \n", message);
    send(new_sock, "YES. Its available\n" , strlen("YES. Its available") , 0 );
   	exit (0);
    	
   	 
	
	return 0;
	
   						
}



 

