
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include    <signal.h>
#define    SERV_PORT      43211
#define MAXLINE 50
static int count;

static void recefrom_init(int signo){
	printf("receive %d datagrams\n",count );
	exit(0);
}

int main(int argc, char const *argv[])
{
	/* code */
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr)); 

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(SERV_PORT);
	bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));

	socklen_t client_len;
	char message[MAXLINE];
	count=0;
	signal(SIGINT,recefrom_init);

	struct sockaddr_in client_addr;
	client_len=sizeof(client_addr);
	for(;;){
		int n=recvfrom(sockfd,message,MAXLINE,0,(struct sockaddr *)&client_addr,&client_len);
		message[n]=0;
		printf("receive %s\n", message);
		
		char send_line[MAXLINE];
		sprintf(send_line,"Hi,%s\n",message);
		sendto(sockfd,send_line,strlen(send_line),0,(struct sockaddr *)&client_addr,client_len);
		count++;
	}
	return 0;
}