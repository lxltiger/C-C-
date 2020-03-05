#include "common.h"


void unix_error(char *msg){
	fprintf(stderr, "%s:%s\n", msg,strerror(errno));
	exit(0);
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
			if(n=1)
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