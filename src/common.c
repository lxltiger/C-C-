#include "common.h"


void unix_error(char *msg){
	fprintf(stderr, "%s:%s\n", msg,strerror(errno));
	exit(0);
}

void app_error(char *msg){
	fprintf(stderr, "%s\n", msg);
	exit(0);
}

void posix_error(int code, char *msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}
void gai_error(int code, char *msg) /* Getaddrinfo-style error */
{
    fprintf(stderr, "%s: %s\n", msg, gai_strerror(code));
    exit(0);
}

pid_t Fork(void){
	pid_t pid;
	if((pid=fork())<0)
		unix_error("fork error");
	return pid;
}

handler_t *Signal(int signum,handler_t *handler){
	struct sigaction action,old_action;
	action.sa_handler=handler;
	sigemptyset(&action.sa_mask);/*block sigs of type being handled*/
	action.sa_flags=SA_RESTART;/*restart syscall if posssible*/
	if(sigaction(signum,&action,&old_action)<0)
		unix_error("signal error");
	return (old_action.sa_handler);
}


/********************************
 * Wrappers for Unix I/O routines
 ********************************/
int Open(const char *pathname,int flags,mode_t mode){
	int rc;
	if((rc=open(pathname,flags,mode))<0)
		unix_error("open error");
	return rc;
}

ssize_t Read(int fd,void *buff,size_t size){
	ssize_t rc;
	if((rc=read(fd,buff,size))<0)
		unix_error("read error");
	return rc;
}
//从buff中向fd写入size个字节，返回值也可能小于期望值size
ssize_t Write(int fd,const void *buff,size_t size){
	ssize_t rc;
	if((rc=write(fd,buff,size))<0)
		unix_error("write error");
	return rc;
}

void Close(int fd) 
{
    int rc;

    if ((rc = close(fd)) < 0)
	unix_error("Close error");
}

int Select(int  n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, 
	   struct timeval *timeout){
	 int rc;

    if ((rc = select(n, readfds, writefds, exceptfds, timeout)) < 0)
	unix_error("Select error");
    return rc;
}

void Stat(const char *filename, struct stat *buf){
	if(stat(filename,buf)<0)
		unix_error("stat error");
}

void Fstat(int fd, struct stat *buf) {
	if(fstat(fd,buf)<0)
		unix_error("fstat error");
}

int Epoll(){
	int epoll_fd;
	if((epoll_fd=epoll_create1(0))==-1)
		unix_error("epoll_create1 error");	

	return epoll_fd;
}


/* Sockets interface wrappers */
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen){
	int rc;
    if ((rc = accept(s, addr, addrlen)) < 0)
	unix_error("Accept error");
    return rc;
}

/*与getaddressinfo相反，这个函数将套接字地址结构转换成对应的主机和服务名字符串
	sa指向大小为salen字节的套接字地址结构
	host指向大小为hostlen字节的缓存区
	serv指向大小为servlen字节的缓冲区
	host或serv如果不想要可以设为NULL，len设为0，但两者只能二选一
	flags可以修改默认行为
		NI_NUMERICHOST 默认返回host中域名，设置此标志返回数字地址字符串
		NI_NUMERICSERV 默认检查/etc/services，如果可能返回服务号而不是端口，设置此标志位跳过检查直接返回端口号
*/
void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, 
                 size_t hostlen, char *serv, size_t servlen, int flags){
	int rc;

    if ((rc = getnameinfo(sa, salen, host, hostlen, serv, 
                          servlen, flags)) != 0) 
        gai_error(rc, "Getnameinfo error");

}

/* Pthreads thread control wrappers */
void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp, 
		    void * (*routine)(void *), void *argp){

	int rc;
	if((rc=pthread_create(tidp,attrp,routine,argp))!=0)
		posix_error(rc,"Pthreads create error");
}


void Pthread_join(pthread_t tid, void **thread_return);
void Pthread_cancel(pthread_t tid);

void Pthread_detach(pthread_t tid){
	int rc;
	if((rc=pthread_detach(tid))!=0)
		posix_error(rc,"Pthread_detach error");
}

void Pthread_exit(void *retval){
	 pthread_exit(retval);
}

pthread_t Pthread_self(void){
	return pthread_self();
}
/*可动态初始化多个线程的共享的全局变量*/
void Pthread_once(pthread_once_t *once_control, void (*init_function)()){
	pthread_once(once_control,init_function);
}


/* POSIX semaphore wrappers */
void Sem_init(sem_t *sem, int pshared, unsigned int value){
	if(sem_init(sem,pshared,value)<0)
		unix_error("Sem_init eror");
}
/*获取锁，如果失败就阻塞*/
void P(sem_t *sem){
	if(sem_wait(sem)<0)
		unix_error("P eror");
}

/*释放锁，唤醒阻塞的线程，如果有多个 只能唤醒一个*/
void V(sem_t *sem){
	if(sem_post(sem)<0)
		unix_error("V error");
}


/* Directory wrappers */
// 以路径为参数，返回指向目录流的指针
DIR *Opendir(const char *name){
	DIR *dirp=opendir(name);
	if(!dirp)
		unix_error("open dir error");
	return dirp;

}
// 返回流dirp中下一个目录项指针，没有返回空
struct dirent *Readdir(DIR *dirp){
	struct dirent *dep;
	errno=0;
	dep=readdir(dirp);
	if((dep==NULL)&&errno!=0)
		unix_error("read dir error");

	return dep;
}


int Closedir(DIR *dirp){
	int rc;
	if((rc=closedir(dirp))<0)
		unix_error("close dir error");

	return rc;
}


/* Standard I/O wrappers */
void Fclose(FILE *fp);
FILE *Fdopen(int fd, const char *type);


char *Fgets(char *ptr, int n, FILE *stream){
	char *rptr;
	if((rptr=fgets(ptr,n,stream))==NULL&&ferror(stream))
		app_error("Fget errno");

	return rptr;
}


FILE *Fopen(const char *filename, const char *mode);

void Fputs(const char *ptr, FILE *stream){
	if(fputs(ptr,stream)==EOF)
		unix_error("Fputs error");
}

size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
void Fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

/* Dynamic storage allocation wrappers */
void *Malloc(size_t size){
	void *p;
	//分配size字节大小的内存  这些字节未经初始化 可能有垃圾值
	if((p=malloc(size))==NULL)
		unix_error("Malloc error");
	return p;

}
void *Realloc(void *ptr, size_t size);

void *Calloc(size_t nmemb, size_t size){
	void* p;
	//分配nmemb个大小为size字节的内存，这块内存都初始化为0 因此分配速度比malloc慢
	if((p=calloc(nmemb,size))==NULL)
		unix_error("Calloc error");
	return p;
}

void Free(void *ptr){
	free(ptr);
}

// 可能返回不足值，比如n=50 但文件只有20个字节
ssize_t rio_readn(int fd,void *usrbuff,size_t n){
	size_t nleft=n;
	ssize_t nread;
	//不要操作原有的指针
	char *bufp=usrbuff;

	while(nleft>0){
		if((nread=read(fd,bufp,nleft))<0){
			//被sig handler中断返回 继续read
			if(errno==EINTR)
				nread=0;
			// 返回读失败的错误号
			else
				return -1;
		}else if(nread==0) /*EOF*/
			break;
		//减少剩余字节数并移动指针 否则可能永远读不完
		nleft-=nread;
		bufp+=nread;

	}
	return (n-nleft);
}
// 不会返回不足值
ssize_t rio_writen(int fd,void *usrbuff,size_t n){
	size_t nleft=n;
	ssize_t nwrite;
	char *bufp=usrbuff;

	while(nleft>0){
		if((nwrite=write(fd,bufp,nleft))<=0){
			if(errno==EINTR)
				nwrite=0;
			else
				return -1;
		}

		nleft-=nwrite;
		bufp+=nwrite;
	}

	return n;
}

/*关联描述符和一个缓存区*/
void rio_readinitb(rio_t *rp,int fd){
	rp->rio_fd=fd;
	rp->rio_cnt=0;
	rp->rio_bufptr=rp->rio_buf;

}
/*对read方法的封装，如果缓存为空，先read一块8k缓存字节，然后把用户请求的字节数从缓冲复制给用户*/
static ssize_t rio_read(rio_t *rp,char *usrbuff,size_t n){
	
	int cnt;
	/*如果缓冲数据已用完 重新读取*/
	while(rp->rio_cnt<=0){
		rp->rio_cnt=read(rp->rio_fd,rp->rio_buf,sizeof(rp->rio_buf));
		if(rp->rio_cnt<0){
			if(errno!=EINTR)
				return -1;
		}else if(rp->rio_cnt==0)
			return 0;
		else 
			rp->rio_bufptr=rp->rio_buf; /*rest buf ptr*/
	}
	//能拷贝的字节数 min(n,rp->rio_cnt)
	cnt=n;
	if(rp->rio_cnt<n)
		cnt=rp->rio_cnt;

	memcpy(usrbuff,rp->rio_bufptr,cnt);
	rp->rio_bufptr+=cnt;
	rp->rio_cnt-=cnt;
	return cnt;
}


/*从缓冲区读取n个字节到usrbuff*/
ssize_t rio_readnb(rio_t *rp,void *usrbuff,size_t n){
	size_t nleft=n;
	ssize_t nread;
	//不要操作原有的指针
	char *bufp=usrbuff;
	while(nleft>0){
		if((nread=rio_read(rp,bufp,nleft))<0)
			return -1;
		else if(nread==0)
			break;
		//减少剩余字节数并移动指针 否则可能永远读不完
		nleft-=nread;
		bufp+=nread;	
	}
	
	return (n-nleft);

}

/*read a line including '\0' with max lens of maxlen*/
ssize_t rio_readlineb(rio_t *rp,void *usrbuff,size_t maxlen){

	char c;
	int n,rc;
	char *bufp=usrbuff;
	for (n = 1; n < maxlen; n++){
		if((rc=rio_read(rp,&c,1))==1){
			*bufp++=c;
			if('\n'==c){
				n++;
				break;
			}
		}else if(rc==0){
			if(n==1)
				return 0;/*EOF nothing read*/
			else
				break; /*EOF with some read*/
		}else
			return -1; /*error*/
	}

	*bufp=0;
	return n-1;
}


ssize_t Rio_readn(int fd, void *usrbuf, size_t nbytes){
	ssize_t n;
	if((n=rio_readn(fd,usrbuf,nbytes))<0)
		unix_error("rio_readn");
	return n;
}

void Rio_writen(int fd, void *usrbuf, size_t n){
	if(rio_writen(fd,usrbuf,n)!=n)
		unix_error("rio write");
}

void Rio_readinitb(rio_t *rp, int fd){
	rio_readinitb(rp,fd);
}

ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t n){
	ssize_t rc;
	if((rc=rio_readnb(rp,usrbuf,n))<0)
		unix_error("rio readnb");
	return rc;
}
ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen){
	ssize_t rc;
	if((rc=rio_readlineb(rp,usrbuf,maxlen))<0)
		unix_error("rio readnb");
	return rc;
}

/*
 * open_clientfd - Open connection to server at <hostname, port> and
 *     return a socket descriptor ready for reading and writing. This
 *     function is reentrant(表示线程安全) and protocol-independent.
 *
 *     On error, returns: 
 *       -2 for getaddrinfo error
 *       -1 with errno set for other errors.
 */
int open_clientfd(char *hostname,char *port){
	int clientfd,rc;
	struct addrinfo hints,*listp,*p;
	//为什么要置零，难道有默认值
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_socktype=SOCK_STREAM;/*tcp连接*/
	hints.ai_flags=AI_NUMERICSERV;/*数字端口*/
	hints.ai_flags |= AI_ADDRCONFIG;/*当主机被配成IPV4时，返回IPV4地址，对IPV6也是一样*/
	
	/*
	*getaddrinfo将主机名、主机地址、服务名和端口号的字符串表示转换成套接字地址结构
	*第一个参数可以是域名也可以是点十分制的IP地址
	*第二个参数可以是服务名，如http，也可以是十进制端口号；这里被hints.ai_flags=AI_NUMERICSERV强制为端口号
	*/
	if((rc=getaddrinfo(hostname,port,&hints,&listp))!=0){
		 fprintf(stderr, "getaddrinfo failed (%s:%s): %s\n", hostname, port, gai_strerror(rc));
        return -2;
	}

	for(p=listp;p;p=p->ai_next){
		//create socket descriptor
		if((clientfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0){
			continue;
		}
		//连接服务端 如果成功跳出循环
		if(connect(clientfd,p->ai_addr,p->ai_addrlen)!=-1)
			break;
		
		if(close(clientfd)<0){
			fprintf(stderr, "open_clientfd: close failed: %s\n", strerror(errno));
            return -1;
		}
	}

	freeaddrinfo(listp);
	if(!p)
		return -1;/*all connects fail*/
	else
		return clientfd;


}

/*  
 * open_listenfd - Open and return a listening socket on port. This
 *     function is reentrant and protocol-independent.
 *
 *     On error, returns: 
 *       -2 for getaddrinfo error
 *       -1 with errno set for other errors.
 */
int open_listenfd(const char *port){
	int listenfd,rc,optval=1;
	struct addrinfo hints,*listp,*p;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_socktype=SOCK_STREAM;/*tcp连接*/
	hints.ai_flags = AI_PASSIVE |AI_ADDRCONFIG;/*AI_PASSIVE表示any IP address*/
	hints.ai_flags|=AI_NUMERICSERV;/*数字端口*/
	if((rc=getaddrinfo(NULL,port,&hints,&listp))!=0){
		 fprintf(stderr, "getaddrinfo failed (port%s): %s\n", port, gai_strerror(rc));
        return -2;
	}

	for(p=listp;p;p=p->ai_next){
		if((listenfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)
			continue;
		 /* Eliminates "Address already in use" error from bind 方便立即开始接受新连接*/
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,  (const void *)&optval , sizeof(int));

        if(bind(listenfd,p->ai_addr,p->ai_addrlen)==0)
        	break;
        //bind fail
        if(close(listenfd)<0)
        	fprintf(stderr, "open_listenfd close failed: %s\n", strerror(errno));
            return -1;
	}

	freeaddrinfo(listp);
	//没找到
	if(!p)
		return -1;
	//监听失败
	if(listen(listenfd,LISTENQ)<0){
		close(listenfd);
		return -1;
	}

	return listenfd;

}

int Open_clientfd(char *hostname,char *port){

	int rc;
	if((rc=open_clientfd(hostname,port))<0)
		unix_error("open clientfd fail");

	return rc;
}
int Open_listenfd(const char *port){
	int rc;
	if((rc=open_listenfd(port))<0)
		unix_error(" Open_listenfd fail");

	return rc;
}