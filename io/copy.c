#include "common.h"


/* 简单模拟cp命令  将一个文件内容复制到另一个文件中，
这里的文件是泛指，终端、管道都可以 ，并不特指普通磁盘文件*/
int main(int argc, char const *argv[]) {

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

    exit(EXIT_SUCCESS);
   return 0;
}



