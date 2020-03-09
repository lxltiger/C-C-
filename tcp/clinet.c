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
	//由于主机采用的小端序列，网络采用的是大端，所以需要转换
	// htons 表示host to net，主机到网络  s表示16位无符号整数，l表示32位
	server_addr.sin_port=htons(12345);
	/*
	将点分十进制IP地址转换为一个二进制的网络字节顺序的IP地址
	如果十进制IP无效函数返回0，其它错误返回-1，并设置errno
	inet_ntop函数作用与其相反
	*/
	inet_pton(AF_INET,argv[1],&server_addr.sin_addr);
	int connect_rt=connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(connect_rt<0){
		error(1,errno,"connect fail");
	}

	sendData(sockfd);
	exit(0);
	
}