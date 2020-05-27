#include "common.h"


void echo(int connfd){
	size_t n;
	char buf[MAXLINE];
	rio_t rio;

	Rio_readinitb(&rio,connfd);
	 while((n=Rio_readlineb(&rio,buf,MAXLINE))!=0){
		printf("server received %d bytes\n", (int)n);
		Rio_writen(connfd,buf,n);
	}
	/* char b[8]={-1,1,4,2,1,-122,-104,'\n'};
	while(read(connfd,buf,MAXLINE)>0){
		printf("read message is : %s",buf);
		Rio_writen(connfd,b,strlen(b));
	} */
	
}