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