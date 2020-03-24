#include "common.h"

#define MAX_EVENTS 5  /* max number of events can be returned from a single epoll_wait */
#define MAX_BUF 1024
/* 虽然epoll监听的fd列表没有上限，但每个监听的fd都占有少量内核内存而且是不可换出的，
监听数量过多会导致内核内存进制，所以需要设置一个上限；/proc/sys/fs/epoll下有一个max_user_watches文件设置了最多监听的fd数量，
默认值是根据系统内存计算而来 */

void epoll_simple(){
    struct epoll_event event;
        struct epoll_event events[MAX_EVENTS];
        char read_buffer[MAX_BUF];
        int running=1;
        int event_count;
        size_t bytes_read;


        int epoll_fd=Epoll_create();
        
        event.events=EPOLLIN;
        event.data.fd=0;
        if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,0,&event)==-1){
            perror("epoll_ctl");
            exit(EXIT_FAILURE);
        }
        while(running){
            printf("\n polling for input..\n");
            event_count=epoll_wait(epoll_fd,events,MAX_EVENTS,30000);
            printf("%d ready event",event_count);
            for (int i = 0; i < event_count; i++)
            {
                printf("reading file descriptor %d ",events[i].data.fd);
                bytes_read=read(events[i].data.fd,read_buffer,MAX_BUF);
                printf("%zd bytes read \n",bytes_read);
                read_buffer[bytes_read]='\0';
                printf("read %s\n",read_buffer);
                if(strncmp(read_buffer,"stop\n",5)==0)
                    running=0;
                
            }
            
        }
        Close(epoll_fd);
    }

/* 使用管道显示epoll对fd的监听 */
int main(int argc, char const *argv[])
{
    int epoll_fd,ready,fd,s,numopenFds;
    struct epoll_event ev;
    struct epoll_event evlist[MAX_EVENTS];
    char buf[MAXBUF];

    if (argc<2||strcmp(argv[1],"--help")==0) {
		fprintf(stderr, "usage: %s file...\n", argv[0]);
		exit(0);
    }
    epoll_fd=Epoll_create();
    for (int i = 1; i < argc; i++){
    //  如果参数是管道符会阻塞直到往管道输入内容
       if((fd=open(argv[i],O_RDONLY))==-1){
           fprintf(stderr, "fail to open:%s\n", strerror(errno));
	        exit(0);
       }

       printf("Opened %s on fd %d\n", argv[i], fd);
       ev.events=EPOLLIN;
       ev.data.fd=fd;
       Epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&ev);
    }
    
    numopenFds=argc-1;
    while(numopenFds>0){
        printf("About to epoll_wait()\n");
        //阻塞的时候可能会被信号中断
        ready=epoll_wait(epoll_fd,evlist,MAXLINE,-1);
        if(-1==ready){
            //如果被中断重启
             printf("restart\n");
            if(errno==EINTR)
                continue;
            else
                unix_error("epoll_wait");
        }
        printf("Ready: %d\n", ready);
        for (int i = 0; i < ready; i++){
            printf(" fd=%d; events: %s%s%s\n", evlist[i].data.fd,
            (evlist[i].events & EPOLLIN) ? "EPOLLIN " : "",
            (evlist[i].events & EPOLLHUP) ? "EPOLLHUP " : "",
            (evlist[i].events & EPOLLERR) ? "EPOLLERR " : "");
            if(evlist[i].events&EPOLLIN){
                s=Read(evlist[i].data.fd,buf,MAX_BUF);
                printf("read %d bytes: %s\n", s, buf);
            }else if(evlist[i].events& (EPOLLHUP | EPOLLERR)){
                printf(" closing fd %d\n", evlist[i].data.fd);
                //多个fd可能对应一个内核中的open file，只有这些fd都关闭了，open file才会被自核自动从监听列表中移除
                Close( evlist[i].data.fd);
                numopenFds--;
            }
        }
        
    }
    printf("All file descriptors closed; bye\n");
    return 0;
}
