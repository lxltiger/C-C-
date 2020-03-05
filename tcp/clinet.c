#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
// #include <zconf.h>
#include <errno.h>


#define BUF_SIZE 102400

void sendData(int sockfd){
	char *buf=malloc(BUF_SIZE+1);
	for (int i = 0; i < BUF_SIZE; ++i)
	{
		buf[i]='a';
	}
	buf[BUF_SIZE]='\0';
	const char *cp=buf;
	size_t remaining=strlen(buf);
	while(remaining){
		int n_written=send(sockfd,cp,remaining,0);
		fprintf(stdout, "send into buffer %ld\n",n_written );
		if(n_written<=0){
			error(1,errno,"send fail");
			return ;
		}
		remaining-=n_written;
		cp+=n_written;
	}


}
int main(int argc, char const *argv[])
{
	/* code */
	if(argc!=2){
		error(1,0,"usage:client <addr>");		
	}
	struct sockaddr_in server_addr;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(12345);
	inet_pton(AF_INET,argv[1],&server_addr.sin_addr);
	int connect_rt=connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(connect_rt<0){
		error(1,errno,"connect fail");
	}

	sendData(sockfd);
	exit(0);
	
}