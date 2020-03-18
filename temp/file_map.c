#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 100
#define handle_error(msg)\
	do{perror(msg);exit(EXIT_FAILURE);}while(0)


//使用内存映射来修改文件 
void modify(int argc, char const *argv[]){
	struct stat sb;
	int fd;
	char *addr;
	if(argc!=2){
		fprintf(stderr, "%s\n", "usage:file_map <file name>");
		exit(1);		
	}

	 fd=open(argv[1],O_RDWR);
	if(fd==-1)
		handle_error("open");

	if(fstat(fd,&sb)==-1)
		handle_error("fstat");
	printf("size of file %zu\n", sb.st_size);
	//MAP_PRIVATE 私有映射无法修改文件;MAP_SHARD不能操作虚拟机下的共享文件，因为linux是无法保证文件的一致性的
	addr=mmap(NULL,sb.st_size,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	
	if(addr==MAP_FAILED)
		handle_error("mmap");
	close(fd);
	printf("%s\n", addr);

	addr[10]='9';
	//如果不手动刷新  munmap前也会刷新 及时这个进程挂了都不影响
	int rt=msync((void *)addr,sb.st_size,MS_SYNC);
	if(rt==-1)
		handle_error("msync");
	rt=munmap(addr,sb.st_size);
	if(rt==-1)
		handle_error("munmap");
}

/*
使用内存映射输出文件部分内容
		-----
		|	|
		|	|
		|	|
		----- -->pa_offset=offset& ~(sysconf(_SC_PAGE_SIZE)-1);页的倍数
		|	|					|map返回的虚拟地址addr是和pa_offset相关的，指向页的开始，write输出从addr+offset-pa_offset开始，长度为length
		|	|-->offset 			|
		|	|	|				| map的起点是pa_offset,这样就是页对齐，长度是length+offset-pa_offset
		-----	|-->length		|
		|	|	|				|
		|	|----
		|	|
		-----
*/

void map_example(int argc, char const *argv[]){

	if(argc!=4){
		fprintf(stderr, "%s\n", "usage:file_map <file name> <offset>  <length>");
		exit(1);		
	}

	int fd;
	struct stat sb;
	off_t offset,pa_offset;
	size_t length;
	char *addr;
	ssize_t s;

	printf("file:%s offset:%s length:%s\n", argv[1],argv[2],argv[3]);
	//第一个参数为文件名
	fd=open(argv[1],O_RDONLY);
	if(fd==-1)
		handle_error("open");
	//获取文件大小
	if(fstat(fd,&sb)==-1)
		handle_error("fstat");
	//第二个参数为偏移量
	offset=atoi(argv[2]);
	//pa_offset 必须是页大小的整数倍
	pa_offset=offset& ~(sysconf(_SC_PAGE_SIZE)-1);
	if(offset>=sb.st_size){
		fprintf(stderr, "%s\n", "偏移量超过文件末尾");
		exit(EXIT_FAILURE);
	}
	if(argc==4){
		length=atoi(argv[3]);
		//确保不要超过文件末尾
		if(offset+length>sb.st_size)
			length=sb.st_size-offset;
	}else{
		length=sb.st_size-offset;
	}
	addr=mmap(NULL,length+offset-pa_offset,PROT_READ,MAP_PRIVATE,fd,pa_offset);
	if(addr==MAP_FAILED)
		handle_error("mmap");
	s=write(STDOUT_FILENO,addr+offset-pa_offset,length);
	if(s!=length){
		if(s==-1)
			handle_error("write");

		fprintf(stderr, "%s\n", "partial write");
		exit(EXIT_FAILURE);
	}
	munmap(addr,length+offset-pa_offset);
	close(fd);
	// exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
	

	return 0;
}