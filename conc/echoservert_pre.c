#include "common.h"
#include "sbuf.h"

#define NTHREADS 4
#define SBUFSIZE 16

void echo_cnt(int connfd);
void* thread(void* vargp);


/*shared buf for connected descriptors*/
sbuf_t sbuf;
/*预线程化的并发echo服务器，使用一个生产者-多个消费者模型*/
int main(int argc, char const *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
    }

    int listenfd,connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
   	pthread_t tid;

   	listenfd=Open_listenfd(argv[1]);

   	sbuf_init(&sbuf,SBUFSIZE);
   	/*创建工作线程*/
   	for (int i = 0; i < NTHREADS; ++i)
   		Pthread_create(&tid,NULL,thread,NULL);
   	
	while(1){
		clientlen=sizeof(struct sockaddr_storage);
		connfd=Accept(listenfd,(SA *)&clientaddr,&clientlen);
		printf("get connection with fd=%d\n", connfd);
		sbuf_insert(&sbuf,connfd);
	}
	return 0;
}

void* thread(void* vargp){
	Pthread_detach(pthread_self());
	while(1){
		int connfd=sbuf_remove(&sbuf);
		printf("worker handle client %d\n", connfd);
		echo_cnt(connfd);
		Close(connfd);
	}
}