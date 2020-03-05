#include "common.h"


int main(int argc, char const *argv[])
{
	
	// int fd=Open(argv[1],O_RDONLY,0);
	// printf("fd:%d\n",fd);
	int n;
	rio_t rio;
	char buf[MAXLINE];

	Rio_readinitb(&rio,STDIN_FILENO);
	while((n=Rio_readlineb(&rio,buf,MAXLINE))){
		Rio_writen(STDOUT_FILENO,buf,n);
	}
	return 0;
}