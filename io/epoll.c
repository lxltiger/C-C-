#include "common.h"

#define MAX_EVENTS 5
#define READ_SIZE 10

int main(int argc, char const *argv[])
{
    struct epoll_event event;
    struct epoll_event events[MAX_EVENTS];
    char read_buffer[READ_SIZE];
    int running=1;
    int event_count;
    size_t bytes_read;


    int epoll_fd=Epoll();
    
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
            bytes_read=read(events[i].data.fd,read_buffer,READ_SIZE);
            printf("%zd bytes read \n",bytes_read);
            read_buffer[bytes_read]='\0';
            printf("read %s\n",read_buffer);
            if(strncmp(read_buffer,"stop\n",5)==0)
                running=0;
            
        }
        
    }
    Close(epoll_fd);

    return 0;
}
