#include "common.h"

static int byte_count;
static sem_t mutex;



static void init_echo_count(){
	Sem_init(&mutex,0,1);
	byte_count=0;
}

void echo_cnt(int connfd){
	char buf[MAXLINE];
	rio_t rio;
	int n;
	static pthread_once_t once=PTHREAD_ONCE_INIT;
	//线程第一次调用时初始化  再次调用就没作用了
	Pthread_once(&once,init_echo_count);
	Rio_readinitb(&rio,connfd);

	while((n=Rio_readlineb(&rio,buf,MAXLINE))!=0){
		P(&mutex);
		byte_count+=n;
		printf("server received %d (%d total) bytes on fd %d\n",  n, byte_count, connfd); 
		V(&mutex);

		Rio_writen(connfd,buf,n);
	}
}