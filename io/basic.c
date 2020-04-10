#include <sys/uio.h>
#include "common.h"


/* 简单模拟cp命令  将一个文件内容复制到另一个文件中，
这里的文件是泛指，终端、管道都可以 ，并不特指普通磁盘文件*/

void copy(int argc, char const *argv[]){
    int inputFd,outputFd,openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[MAXBUF];

   if (argc !=3 ||strcmp(argv[1],"--help")==0) 
       usageErr("usage: %s from_file to_file\n", argv[0]);
   

    inputFd=Open(argv[1],O_RDONLY,0);
    
    //flag说明：O_CREAT如果文件不存在则创建
    //O_WRONLY文件可读可写，O_TRUNC如果文件存在则截断
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    //文件的权限,如果不是用来创建文件，这个参数可以省略
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;      /* rw-rw-rw- */
    outputFd=Open(argv[2],openFlags,filePerms);
    while((numRead=read(inputFd,buf,MAXBUF))>0){
        if(write(outputFd,buf,numRead)!=numRead)
            fatal("couldn't write whole buffer");
    }
    
    if(numRead==-1)
        errExit("read");

    Close(inputFd);
    Close(outputFd);

}

/* tee命令的模拟，将标准输入的内容一边输出到终端一边写入到指定文件 */
void tee(int argc, char const *argv[]){
    int outputFd,openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[MAXBUF];

   if (argc <2 ||argc >3||strcmp(argv[1],"--help")==0) 
       usageErr("usage: %s <-a> fileName\n", argv[0]);
   
    
    //设置文件的参数，如果文件存在默认截取文件
    openFlags = O_CREAT | O_WRONLY  ;
    //是否是添加
    if(argc ==3&&strcmp(argv[1],"-a")==0)
        openFlags|= O_APPEND;
    else
        openFlags|= O_TRUNC;
    
    
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;    
    outputFd=Open(argc==2?argv[1]:argv[2],openFlags,filePerms);
    while((numRead=read(STDIN_FILENO,buf,MAXBUF))>0){
        if(write(outputFd,buf,numRead)!=numRead)
            fatal("couldn't write whole buffer to output");
        
        if(write(STDOUT_FILENO,buf,numRead)!=numRead)
            fatal("couldn't write whole buffer to stdout");
    }
    
    if(numRead==-1)
        errExit("read");

    Close(outputFd);    
}

/* 使用多数据源往一个文件中写入字节，及逆操作 */
void scatter_gather_io(int argc, char const *argv[]){
    int outputFd,openFlags;
    mode_t filePerms;
    ssize_t numRead;
    ssize_t numWrite;

    if (argc !=2||strcmp(argv[1],"--help")==0) 
       usageErr("usage: %s  fileName\n", argv[0]);
   
    int x=6;
    char buf[10]="abc";
    struct iovec iov[2];
    int total=0;
    iov[0].iov_base=&x;
    iov[0].iov_len=sizeof(x);
    total+=iov[0].iov_len;

    iov[1].iov_base=buf;
    iov[1].iov_len=10;
    total+=iov[1].iov_len;

    openFlags = O_CREAT | O_RDWR | O_TRUNC ;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH; 
    outputFd=Open(argv[1],openFlags,filePerms);
    //将多个源的字节按顺序写到一个文件，整个过程是原子操作
    numWrite=writev(outputFd,iov,2);
    if (numWrite == -1)
        errExit("writev");

    if (numWrite < total)
        printf("Write fewer bytes than requested\n");

    printf("total bytes requested: %ld; bytes write: %ld\n",(long) total, (long) numWrite);

    struct iovec iov_read[2];
    int y=0;
    char buf_read[10];
    int total_read=0;
    iov_read[0].iov_base=&y;
    iov_read[0].iov_len=sizeof(y);
    total_read+=iov_read[0].iov_len;

    iov_read[1].iov_base=buf_read;
    iov_read[1].iov_len=10;
    total_read+=iov_read[1].iov_len;

    //重新设置文件的偏移量，从头开始读
    lseek(outputFd, 0, SEEK_SET);
    //将文件描述符的字节依此填充多个buf，填满一个才继续下一个，整个过程是原子操作
    numRead=readv(outputFd,iov_read,2);
    if (numRead == -1)
        errExit("readv");

    if (numRead < total_read)
        printf("Read fewer bytes than requested\n");

    printf("buf read:x=%d,buf=%s",y,buf_read);

    Close(outputFd);
}

int main(int argc, char const *argv[]) {

    
    int openFlags = O_CREAT | O_RDWR |O_APPEND  ;
    mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH; 
    int outputFd=Open(argv[1],openFlags,filePerms);

    for (size_t i = 0; i < 10; i++){
        write(outputFd,argv[2],strlen(argv[2]));
        // sleep(1);
    }
    
    exit(EXIT_SUCCESS);
}



