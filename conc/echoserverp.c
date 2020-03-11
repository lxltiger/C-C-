#include "common.h"

void echo(int connfd);

void sigchild_handler(int sig){
	printf("receiver sig： %d\n",sig);
	while(waitpid(-1,0,WNOHANG)>0)
		;
	return ;
}
/*基于进程的并发echo服务器*/
int main(int argc, char const *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
    }

    int listenfd,connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    // char client_hostname[MAXLINE],client_port[MAXLINE];
    Signal(SIGCHLD,sigchild_handler);
    listenfd=Open_listenfd(argv[1]);
	while(1){
		clientlen=sizeof(struct sockaddr_storage);
		connfd=Accept(listenfd,(SA *)&clientaddr,&clientlen);
		if(Fork()==0){
			Close(listenfd);/*子进程先关闭监听描述符*/
			echo(connfd);
			Close(connfd);
			exit(0);
		}

		Close(connfd);/*父进程关闭连接描述符，否则这个打开的文件无法关闭，导致内存泄漏*/
	}
	return 0;
}