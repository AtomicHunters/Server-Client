#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

	int port = atoi(argv[1]);
	int alrTime= atoi(argv[2]);
	if(argc >= 2){
		printf("Port: %d\n Time: %d\n", port, alrTime);
		printf("** the server uses port# %d to listen with %d for alarm **\n", port, alrTime);
		printf("** the server will be terminated after %d seconds of inactivity\n", alrTime);
		system("date; hostname; whoami; ps; ls -l");
	}
	else {
		perror("Please input the port and time as arguments\n");
	}
	
    char sendBuff[1025];
    time_t ticks; 
	printf("Argv[1] = %d\n\n", port);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
	alarm(alrTime);
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
	if(connfd > 0){
		alarm(0);	
		system("netstat -an | grep $port");
	}
        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 
        close(connfd);
        sleep(1);
     }
	printf("the server ends**\n");
	system("date; hostname; whoami; ps; ls-l");
}
