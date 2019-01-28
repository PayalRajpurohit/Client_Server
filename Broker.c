#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    
#include<limits.h>
#include<pthread.h> 
#define PORT 8888
#define SIZE 1000

int front = 0;
int rear = -1;

struct holder{
	int service_random_number;
	int port_random_number;
	char IPaddress[10];
};

struct holder service_holder[SIZE];

int random_generate() 
{
	int n = rand() % 100 + 1; 
	return n;
}
	
int generate_port(int sr_no)
{
	int port_number;
	port_number = 8000 + sr_no;
	return port_number;
}


void insert(int sr_no, int pr_no) {
	  ++rear;
      service_holder[rear].service_random_number=sr_no;
      service_holder[rear].port_random_number=pr_no;
      strcpy(service_holder[rear].IPaddress,"127.0.0.1");
      
}

void removedata() {

   int data_sr = service_holder[front].service_random_number;
   int data_pr = service_holder[front].service_random_number;
   front++;    
}

int find_element(int n){
	for(int i=front;i<=rear;i++){
		if (service_holder[i].service_random_number==n){
			return 1;
		}
		
	} 
	
	return 0;

}

void display(){
	for(int i=front;i<=rear;i++){
		printf("%d\t",service_holder[i].service_random_number);
		printf("%d\t",service_holder[i].port_random_number);
		printf("%s\n",service_holder[i].IPaddress);
	}

}

void* process1()
{
	int sock , new_sock , c, read_size,ch;
    struct sockaddr_in server , client;
    char *message , c_message[1000];
    sock = socket(AF_INET , SOCK_STREAM , 0);
    puts("Socket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );

    bind(sock,(struct sockaddr *)&server , sizeof(server));

    listen(sock , 3);
    c = sizeof(struct sockaddr_in);
    puts("Waiting for incoming connections...");
    while(1)
    {	 
		new_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
		printf("Connection done\n");
			 
		ch = fork();
		if(ch==0)
		{
			while(1)
			{
				if( (read_size = recv(new_sock , c_message , 2000 , 0)) > 0 )
    			{
    					printf("%d\n",atoi(c_message));
    					int n = find_element(atoi(c_message));
   
    				  if(n==1)
                      {
    				  	write(new_sock , "YES" , strlen("YES")); 	
    				  	exit(0);
    				  }
                      else
                      {
                        write(new_sock, "Requested service not available" , strlen("Requested service not available"));
                      }
    				  
      				 
   				 }
			}
			exit(0);
		}
	}
		return 0;
}

void* process2()
 {
 	int sr_no=0;
 	int n;
 	while(1) {
 	sr_no=random_generate();
 	insert(sr_no,generate_port(sr_no));
 	display();
 	printf("\n------------------------------------\n");
 	sleep(3);
 	sr_no=random_generate();
 	insert(sr_no,generate_port(sr_no));
 	display();
 	printf("\n------------------------------------\n");
 	sleep(3);
 	removedata();
 	display();
 	printf("\n------------------------------------\n");
 	}
 }
int main()
 {
	pthread_t process1_thread, process2_thread; 
	
    pthread_create(&process1_thread, NULL, process1, NULL); 
	pthread_create(&process2_thread, NULL, process2, NULL);
    pthread_join(process1_thread, NULL);
	pthread_join(process2_thread, NULL);	
    
    exit(0);

 }