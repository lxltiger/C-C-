#include "common.h"

void echo(int connfd);

void *thread(void *vargp);


/*基于线程的并发echo服务器*/
int main(int argc, char const *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
    }

    int listenfd,*connfdp;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
   	pthread_t tid;

    listenfd=Open_listenfd(argv[1]);
	while(1){
		clientlen=sizeof(struct sockaddr_storage);
		connfdp=Malloc(sizeof(int));
		*connfdp=Accept(listenfd,(SA *)&clientaddr,&clientlen);
		Pthread_create(&tid,NULL,thread,connfdp);
	}
	return 0;
}

void *thread(void *vargp){
	int *connfdp=(int *)vargp;
	int connfd=*connfdp;
	//处理连接之前分离自己 这样方法结束后由系统回自动回收资源，而不需要主线程显示的等待
	Pthread_detach(pthread_self());
	Free(vargp);
	echo(connfd);
	Close(connfd);
	return NULL;
}