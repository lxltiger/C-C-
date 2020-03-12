#include "common.h"

#define N 2

void* thread(void* vargp);

char** ptr;

int main(int argc, char const *argv[])
{
	pthread_t tid;
	char* msgs[N]={
		"Hello from foo",
		"Hello from bar"
	};
	//栈中的二级指针
	ptr=msgs;
	for (int i = 0; i < N; ++i)
		Pthread_create(&tid,NULL,thread,(void *)i);
	
	Pthread_exit(NULL);
	return 0;
}


void* thread(void* vargp){
	//本地自动变量 每个线程都有一个i的实列
	int i=(int)vargp;
	//本地静态变量 内存中只有一个cnt实列 线程共享
	static int cnt=0;
	//ptr是指向主线程栈中变量的指针，说明线程能间接引用其它线程栈的内容
	printf("[%d]:%s (cnt=%d)\n",i,ptr[i],++cnt);
	return NULL;
}