#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int main(int argc, char *argv[])
{
    //char ip[];  // default IP of the server
    //int port = (int) *argv[2];         // default port# of the server

    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 
	int port = atoi(argv[2]);
	if(argc >= 2){
		printf("IPv4: %d\nPort: %d\n", port, argv[1]);
		printf("** the client is to connect to the server of IP# %d and Port# %d **\n", argv[1], port);
		printf("** the client will be terminated");
		system("date; hostname; whoami; ps; ls -l");
	}
	else{
		printf("Please input the IP and port numbers\n");	
	}

	printf("Ip is: %d\n\n", *argv[1]);
    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port); 
    //argv[1] = ip;

    system(" date; hostname; whoami ");
    system(" netstat -aont | grep \" `hostname -i`:23456 \" ");

    printf("\n timeClient: connecting to %d  Port#%d \n", argv[1], port);


    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    printf("\n timeClient: connected to timeServer. \n");
    system("ps");
    system(" netstat -aont | grep \":23456 \" ");
    printf("\n\n");

    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
	   exit(0);
    } 

    printf("\n timeClient: now terminated. \n");
	printf("** the client ends **\n");
	system("date; hostname; whoami; ps; ls -l");
    return 0;
}
