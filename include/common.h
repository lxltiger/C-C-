#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h> 

#include "error_functions.h"


/* Unfortunately some UNIX implementations define FALSE and TRUE -
   here we'll undefine them， */

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum { FALSE, TRUE } Boolean;


#define DEF_MODE   S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
#define DEF_UMASK  S_IWGRP|S_IWOTH


/* Simplifies calls to bind(), connect(), and accept() */
/* $begin sockaddrdef */
typedef struct sockaddr SA;


/*rio package 持久化状态*/
#define RIO_BUFSIZE 8192
typedef struct {
	int rio_fd;
	int rio_cnt;/*unread byte in internal buf*/
	char *rio_bufptr;/*next unread byte in internal buf*/
	char rio_buf[RIO_BUFSIZE];
}rio_t;

/* Misc constants */
#define	MAXLINE	 8192  /* Max text line length */
#define MAXBUF   8192  /* Max I/O buffer size */
#define LISTENQ  1024  /* Second argument to listen() */

//一些小函数使用宏来封装的效果比 inline 关键字要更好
#define ngx_tolower(c) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define ngx_toupper(c) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)
#define ngx_memzero(buf, n) (void) memset(buf, 0, n)

/* Our own error-handling functions */
void unix_error(char *msg);
void posix_error(int code, char *msg);
void dns_error(char *msg);
void gai_error(int code, char *msg);
void app_error(char *msg);
void usageErr(const char *format, ...);


// void errMsg(const char *format, ...);
// void errExit(const char *format, ...)  ;
// void err_exit(const char *format, ...)  ;
// void errExitEN(int errnum, const char *format, ...)  ;
// void fatal(const char *format, ...)  ;
// void usageErr(const char *format, ...)  ;
// void cmdLineErr(const char *format, ...)  ;

/* Process control wrappers */
pid_t Fork(void);
void Execve(const char *filename, char *const argv[], char *const envp[]);
pid_t Wait(int *status);
pid_t Waitpid(pid_t pid, int *iptr, int options);
void Kill(pid_t pid, int signum);
unsigned int Sleep(unsigned int secs);
void Pause(void);
unsigned int Alarm(unsigned int seconds);
void Setpgid(pid_t pid, pid_t pgid);
pid_t Getpgrp();

/* Signal wrappers */
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);
void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
void Sigemptyset(sigset_t *set);
void Sigfillset(sigset_t *set);
void Sigaddset(sigset_t *set, int signum);
void Sigdelset(sigset_t *set, int signum);
int Sigismember(const sigset_t *set, int signum);
int Sigsuspend(const sigset_t *set);

// UNIX IO Wrapper--------//
int Open(const char *pathname,int flags,mode_t mode);

/*
参数说明：size_t是unsigned long，ssize_t 是long
从文件描述符中读取size个字节到buff缓存中
若成功则返回读的字节数 可能小于期望值size 需要重复读取
若是EOF返回0
出错返回-1
*/
ssize_t Read(int fd,void *buff,size_t size);
//从buff中向fd写入size个字节，返回值也可能小于期望值size
ssize_t Write(int fd,const void *buff,size_t size);
void Close(int fd);
int Select(int  n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, 
	   struct timeval *timeout);
void Stat(const char *filename, struct stat *buf);
void Fstat(int fd, struct stat *buf) ;


int Epoll_create();
int Epoll_ctl(int epfd, int op, int fd, struct epoll_event *ev);
// UNIX IO Wrapper--------//

/* Sockets interface wrappers */
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);

/* Protocol independent wrappers */
void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, 
                 size_t hostlen, char *serv, size_t servlen, int flags);


/* Pthreads thread control wrappers */
void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp, 
		    void * (*routine)(void *), void *argp);
void Pthread_join(pthread_t tid, void **thread_return);
void Pthread_cancel(pthread_t tid);
void Pthread_detach(pthread_t tid);
void Pthread_exit(void *retval);
pthread_t Pthread_self(void);
void Pthread_once(pthread_once_t *once_control, void (*init_function)());

/* POSIX semaphore wrappers */
void Sem_init(sem_t *sem, int pshared, unsigned int value);
void P(sem_t *sem);
void V(sem_t *sem);

/* Directory wrappers */
DIR *Opendir(const char *name);
struct dirent *Readdir(DIR *dirp);
int Closedir(DIR *dirp);

/* Standard I/O wrappers */
void Fclose(FILE *fp);
FILE *Fdopen(int fd, const char *type);
char *Fgets(char *ptr, int n, FILE *stream);
FILE *Fopen(const char *filename, const char *mode);
void Fputs(const char *ptr, FILE *stream);
size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
void Fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

/* Dynamic storage allocation wrappers */
void *Malloc(size_t size);
void *Realloc(void *ptr, size_t size);
void *Calloc(size_t nmemb, size_t size);
void Free(void *ptr);


/*RIO package rio_readn和rio_writen没有缓冲，直接在文件和内存间传输数据*/
// rio_readn在遇到EOF时只能返回不足值
ssize_t rio_readn(int fd,void *usrbuff,size_t n);
// 不会返回不足值
ssize_t rio_writen(int fd,void *usrbuff,size_t n);
void rio_readinitb(rio_t *rp,int fd);
ssize_t rio_readnb(rio_t *rp,void *usrbuff,size_t n);
ssize_t rio_readlineb(rio_t *rp,void *usrbuff,size_t maxlen);

/* Wrappers for Rio package */
ssize_t Rio_readn(int fd, void *usrbuf, size_t n);
void Rio_writen(int fd, void *usrbuf, size_t n);
void Rio_readinitb(rio_t *rp, int fd); 
ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t n);
ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);


int open_clientfd(char *hostname,char *port);
int open_listenfd(const char *port);

int Open_clientfd(char *hostname,char *port);
int Open_listenfd(const char *port);




#endif