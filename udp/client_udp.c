#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#define MAXLINE 50
#define    SERV_PORT      43211
int main(int argc, char const *argv[])
{
	if(argc!=2){
		error(1,0,"usage:udp_clinet <IP Address>");
	}
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(SERV_PORT);
	inet_pton(AF_INET,argv[1],&server_addr.sin_addr);

	socklen_t server_len=sizeof(server_addr);
	struct sockaddr *reply_addr;
	reply_addr=malloc(server_len);

	char send_line[MAXLINE], recv_line[MAXLINE+1];
	socklen_t len;
	int n;
	//get input from keyboard
	while(fgets(send_line,MAXLINE,stdin)!=NULL){
		int i=strlen(send_line);
		//replace enter with '\0'
		if(send_line[i-1]=='\n'){
			send_line[i-1]=0;
		}

		printf("preapre to  sending %s\n", send_line);
		size_t rt=sendto(sockfd,send_line,strlen(send_line),0,(struct sockaddr *)&server_addr,server_len);
		if(rt<0){
			error(1,errno,"send fail ");
		}
		printf("sending %s with bytes: %zu\n",send_line,rt);

		len=0;
		//如果没有回应 会阻塞在此
		n=recvfrom(sockfd,recv_line,MAXLINE,0,reply_addr,&len);
		if(n<0){
			error(1,errno,"reve fail ");
		}
		recv_line[n]=0;
		fputs(recv_line,stdout);
		fputs("\n",stdout);

	}

	exit(0);

	return 0;
}