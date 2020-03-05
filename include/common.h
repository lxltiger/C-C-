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

// UNIX IO Wrapper

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
#endif