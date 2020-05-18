#include "common.h"

// gcc -o thread  thread_demo.c -pthread 使用pthread库，需要加-pthread参数
//gcc null.c -o null -g   
// gdb null  使用gdb调式 demo for nano
//valgrind --leak-check=full ./null
typedef struct Arg
{
	int a;
	int  b;
} my_arg;


void *fun(void *p){
	my_arg* arg=(my_arg*)p;
	printf("a=%d,b=%d\n", arg->a,arg->b);
	return NULL;
}

int main(int argc, char const *argv[])
{
	
	my_arg arg={10,20};
	// 对等线程，可以存放新线程的ID
	pthread_t t1;
	int rc=pthread_create(&t1,NULL,fun,&arg);
	if(rc==0){
		//阻塞到t1终止
		rc=pthread_join(t1,NULL);
	}
	return 0;
}