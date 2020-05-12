#include "common.h"


typedef struct 
{
	int maxfd; /*read_set中最大描述符*/
	fd_set read_set;/*set of all active descriptor*/
	fd_set ready_set;/*subset of descriptor ready for reading*/
	int nready;/*number of ready descriptor for select*/
	int maxi;/*clientfd数组最大索引*/
	int clientfd[FD_SETSIZE];/*活跃的描述符集合*/
	rio_t clientrio[FD_SETSIZE]/*活跃的读缓冲集合*/
} pool;

void init_pool(int listenfd,pool *p);
void add_client(int connfd,pool *p);
void check_clients(pool *p);


int byte_cnt=0;/*server接受到的字节总数*/
/*基于IO多路复用的并发echo服务器，单进程 高效 但无法利用多核优势*/

/* 
FD_ZERO 用来将这个向量的所有元素都设置成 0；
FD_SET 用来把对应套接字 fd 的元素，a[fd]设置成 1；
FD_CLR 用来把对应套接字 fd 的元素，a[fd]设置成 0；
FD_ISSET 对这个向量进行检测，判断出对应套接字的元素 a[fd]是 0 还是 1。
其中 0 代表不需要处理，1 代表需要处理。

 */

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
    }

    int listenfd,connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    listenfd=Open_listenfd(argv[1]);
    init_pool(listenfd,&pool);

    while(1){
    	//read set在运行过程中会不断变化，有添加进来的 有移出去的描述符
    	pool.ready_set=pool.read_set;
		/* 最后一个参数是timeval，可能值如下：
		第一个可能是设置成空 (NULL)，表示如果没有 I/O 事件发生，则 select 一直等待下去。
		第二个可能是设置一个非零的值，这个表示等待固定的一段时间后从 select 阻塞调用中返回。
		第三个可能是将 tv_sec 和 tv_usec 都设置成 0，表示根本不等待，检测完毕立即返回。这种情况使用得比较少。 */
    	pool.nready=Select(pool.maxfd+1,&pool.ready_set,NULL,NULL,NULL);
		/*如果监听的描述符准备好了 将客户端加入pool*/
    	if(FD_ISSET(listenfd,&pool.ready_set)){
    		clientlen=sizeof(struct sockaddr_storage);
			connfd=Accept(listenfd,(SA *)&clientaddr,&clientlen);
			add_client(connfd,&pool);
    	}

    	check_clients(&pool);
    }
	return 0;
}

void init_pool(int listenfd,pool *p){
	/*此时没有连接描述符*/

	//maxi是clientfd数组最大索引
	p->maxi=-1;
	for (int i = 0; i < FD_SETSIZE; ++i)
		p->clientfd[i]=-1;
	// 此时监听描述符是select read 集合唯一的成员
	p->maxfd=listenfd;
	FD_ZERO(&p->read_set);
	FD_SET(listenfd,&p->read_set);

}

void add_client(int connfd,pool *p){
	p->nready--;
	for (int i = 0; i < FD_SETSIZE; ++i){
		if(p->clientfd[i]<0){
			//为连接描述符找到合适位置
			p->clientfd[i]=connfd;
			//初始化rio
			Rio_readinitb(&p->clientrio[i],connfd);
			//将连接描述符添加到read set
			FD_SET(connfd,&p->read_set);
			//更新最大连接描述符
			if(connfd>p->maxfd)
				p->maxfd=connfd;
			// 更新clientfd数组的最大索引
			if(i>p->maxi)
				p->maxi=i;

			break;
		}
		if(i==FD_SETSIZE)
			app_error("add client error:Too many clients");
	}
}

void check_clients(pool *p){
	int connfd,n;
	char buf[MAXLINE];
	rio_t rio;

	for (int i = 0; (i<=p->maxi)&&(p->nready>0); ++i){
		connfd=p->clientfd[i];
		rio=p->clientrio[i];

		/*如果描述准备好了 回应文本*/
		if(connfd>0&&FD_ISSET(connfd,&p->ready_set)){
			p->nready--;
			if((n=Rio_readlineb(&rio,buf,MAXLINE))!=0){
				byte_cnt+=n;
				printf("receive %d(%d total)bytes on fd %d\n",n,byte_cnt,connfd);
				Rio_writen(connfd,buf,n);
			}else{
				/*检测到EOF*/
				Close(connfd);
				FD_CLR(connfd,&p->read_set);
				p->clientfd[i]=-1;
			}

		}
	}


}