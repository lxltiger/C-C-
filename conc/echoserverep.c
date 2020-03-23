#include "common.h"

 #define MAX_EVENTS 10


void do_read(int epollfd, int fd,char* buf);
void do_write(int epollfd, int fd,char* buf);
void add_event(int epollfd,int fd,int state);
void delete_event(int epolled,int fd,int state);
void modify_event(int epolled,int fd,int state);


int byte_cnt=0;/*server接受到的字节总数*/
/*基于Epoll的多路复用的并发echo服务器，单进程 高效 但无法利用多核优势*/
int main(int argc, char const *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
    }
	struct epoll_event events[MAX_EVENTS];
    int listen_sock, conn_sock, nfds, epollfd;
    
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

	char buf[MAXBUF];

    listen_sock=Open_listenfd(argv[1]);
	
	epollfd=epoll_create1(0);
	if(epollfd==-1){
		perror("epoll create1");
		exit(EXIT_FAILURE);
	}

	
	add_event(epollfd,listen_sock,EPOLLIN);

	for(;;){
		nfds=epoll_wait(epollfd,events,MAX_EVENTS,-1);
		if(nfds==-1){
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < nfds; i++)
		{
			if(events[i].data.fd==listen_sock){
				clientlen=sizeof(struct sockaddr_storage);
				conn_sock=Accept(listen_sock,(SA *)&clientaddr,&clientlen);
				// setnonblocking(conn_sock);
				 printf("accept a new client: \n");
				add_event(epollfd,conn_sock,EPOLLIN /* | EPOLLET */);
			}else if(events[i].events&EPOLLIN){
				do_read(epollfd, events[i].data.fd,buf);
			}else if(events[i].events&EPOLLOUT){
				do_write(epollfd, events[i].data.fd,buf);
			}
		}
		
	}
    
	if(close(epollfd)){
    	fprintf(stderr, "Failed to close epoll file descriptor\n");
    	return 1;
  	}
	return 0;
}

void do_read(int epollfd, int fd,char* buf){
	int nread=read(fd,buf,MAXBUF);
	if (nread == -1){
         perror("read error:");
        close(fd);
         delete_event(epollfd,fd,EPOLLIN);
    }else if (nread == 0){
         fprintf(stderr,"client close.\n");
         close(fd);
        delete_event(epollfd,fd,EPOLLIN);
    }else{
        printf("read message is : %s",buf);
        //修改描述符对应的事件，由读改为写
        modify_event(epollfd,fd,EPOLLOUT);
    }

}
void do_write(int epollfd, int fd,char* buf){
	int nwrite;
    nwrite = write(fd,buf,strlen(buf));
    if (nwrite == -1){
        perror("write error:");
        close(fd);
        delete_event(epollfd,fd,EPOLLOUT);
    }else
        modify_event(epollfd,fd,EPOLLIN);
    memset(buf,0,MAXBUF);
}

void add_event(int epollfd,int fd,int state){
	struct epoll_event ev;
	ev.events=state;
	ev.data.fd=fd;
	if(epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev)==-1){
		perror("epoll_ctl");
		exit(EXIT_FAILURE);
	}
}
void delete_event(int epollfd,int fd,int state){
	struct epoll_event ev;
	ev.events=state;
	ev.data.fd=fd;
	if(epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev)==-1){
		perror("epoll_ctl");
		exit(EXIT_FAILURE);
	}
}
void modify_event(int epollfd,int fd,int state){
	struct epoll_event ev;
	ev.events=state;
	ev.data.fd=fd;
	if(epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev)==-1){
		perror("epoll_ctl");
		exit(EXIT_FAILURE);
	}
}

