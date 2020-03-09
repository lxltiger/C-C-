#include "common.h"

void cpfile(){
	int n;
	rio_t rio;
	char buf[MAXLINE];

	Rio_readinitb(&rio,STDIN_FILENO);
	while((n=Rio_readlineb(&rio,buf,MAXLINE))){
		Rio_writen(STDOUT_FILENO,buf,n);
	}
}

void statcheck(int argc, char const *argv[]){
	if(argc!=2){
		fprintf(stderr, "%s\n", "usage:test filename");
		exit(-1);
	}

	struct stat stat;
	char *type,*readok;
	Stat(argv[1],&stat);
	if(S_ISREG(stat.st_mode))
		type="regular ";
	else if(S_ISDIR(stat.st_mode))
		type="dir";
	else
		type="other";

	if((stat.st_mode&S_IRUSR))
		readok="yes";
	else
		readok="no";

	printf("type %s,read %s\n",type,readok);
}

void read_dir(int argc, char const *argv[]){
	if(argc!=2){
		fprintf(stderr, "%s\n", "usage:test dir or . for current dir");
		exit(-1);
	}
	//目录流
	DIR *streamp;
	struct dirent *dep;
	streamp=Opendir(argv[1]);

	errno=0;
	//读取目录下的文件
	while((dep=readdir(streamp))!=NULL)
		printf("found file %s\n", dep->d_name);
	
	if(errno!=0)
		unix_error("read dir error");		

	Closedir(streamp);
}


	/*
	十六进制到10进制点分IP地址
	自己实现的将int整数转换成IP地址
	使用无符号的指针类型 unsigned char *p=(char *)src;
	将指针所指的值格式化成无符号的整数值 sprintf(dst,"%u.%u.%u.%u",*(p+3),*(p+2),*(p+1),*p);
	*/
void hex2dd(int argc, char const *argv[]){
	
	if(argc!=2){
		fprintf(stderr, "usage:%s hex num\n", argv[0]);
		exit(0);
	}
	
	//主机序列地址
	uint32_t addr;
	// IP地址结构体，网络字节序列 in for internet
	struct in_addr inaddr;
	//存放十进制的点分IP
	char dst[48];
	//输入参数是十六进制字符串，提取成十进制整树，是主机序列
	sscanf(argv[1],"%x",&addr);
	//将主机序列换成网络序列
	inaddr.s_addr=htonl(addr);
	//将网络序列的整数IP地址转换成字符串形式的点分IP地址
	if(!inet_ntop(AF_INET,&inaddr.s_addr,dst,48))
		unix_error("inet ntop");
	
	printf("%s\n",dst);

}

void dd2hex(int argc, char const *argv[]){
	if(argc!=2){
		fprintf(stderr, "usage:%s <dotted-decimal>\n", argv[0]);
		exit(0);
	}

	struct in_addr inaddr;
	int rc=inet_pton(AF_INET,argv[1],&inaddr.s_addr);
	if(rc==0)
		app_error("inet_pton:invalid dotted-decimal address");
	else if(rc<0)
		unix_error("inet_pton error");

	printf("0x%x\n", ntohl(inaddr.s_addr));
}
int main(int argc, char const *argv[])
{
	
	return 0;
}