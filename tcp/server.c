#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>



/* 从socketfd描述字中读取"size"个字节. */
size_t  readn(int sockfd,void *buffer,size_t size){
	char *buffer_point=buffer;
	int length=size;
	while(length>0){
		//要求内核从套接字描述符读取size大小的字节，存放在buffer缓存中
		int result=read(sockfd,buffer_point,size);
		if(result<0){
			if(errno==EINTR)
				continue;
			else
				return -1;
		}else if(result==0)
			break;
		length-=result;
		buffer_point+=result;
	}

	return (size-length);
}

void read_data(int sockfd)
{
	ssize_t n;
	char buff[1024];
	int time=0;
	for(;;){
		fprintf(stdout, "block in read_data\n" );
		if((n=readn(sockfd,buff,1024))==0){
			return ;
		}
		time++;
		fprintf(stdout, "1k read for %d\n",time);
		usleep(1000);
	}
}

int main(int argc, char const *argv[])
{
	/* code */
	//描述终端IP和端口信息的结构体
	struct sockaddr_in server_addr,client_addr;
	
	/*
	*1.create socket
	*AF_INET IP4地址类型
	*SOCK_STREAM 字节流
	*/
	int listenfd=socket(AF_INET,SOCK_STREAM,0);

	bzero(&server_addr,sizeof(server_addr));
	//初始化服务端sock结构体信息
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(12345);

	// 2.绑定到一个端口

	bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	// 监听客户端的访问,backlog为1024
	listen(listenfd,1024);

	int clinet_len,conn_fd;
	for (; ;)
	{
		clinet_len=sizeof(client_addr);
		conn_fd=accept(listenfd,(struct sockaddr *)&client_addr,&clinet_len);
		read_data(conn_fd);
		close(conn_fd);
		
	}
	return 0;
}