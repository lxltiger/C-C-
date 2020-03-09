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

/* Our own error-handling functions */
void unix_error(char *msg);
void posix_error(int code, char *msg);
void dns_error(char *msg);
void gai_error(int code, char *msg);
void app_error(char *msg);




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
void Stat(const char *filename, struct stat *buf);
void Fstat(int fd, struct stat *buf) ;
// UNIX IO Wrapper--------//

/* Sockets interface wrappers */
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);

/* Protocol independent wrappers */
void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, 
                 size_t hostlen, char *serv, size_t servlen, int flags);

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
int open_listenfd(char *port);

int Open_clientfd(char *hostname,char *port);
int Open_listenfd(char *port);
#endif