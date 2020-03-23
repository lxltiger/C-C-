#include <stdio.h>
#include <string.h>
/*  the pointer to function */

int  add(int a,int b){
	return a+b;
}

int minus(int a,int b){
	return a-b;
}

void print(int *p,int len){
	for (int i = 0; i < len; ++i)
	{
		printf("%d-", *(p+i));
	}
	printf("\n");
}

//使用函数指针作为函数的参数
int func(int (*p)(int,int),int a,int b){
	// 通过函数指针调用函数
	 return p(a,b);
}

// 重新初始化数组
void reset(){
	int buf[10]={1,3,4,5,6};
	// 要初始化的数组，初始化的纸，和内存大小
	memset(buf,0,sizeof(buf));
	print(buf,10);
}

// 数组的拷贝，避免拷贝过程的内存重叠
void copy(){
	int buf1[10]={1,3,4,232325};
	int buf2[10]={0};
	//参数buf1指目标地址，参数buf2指原地址，拷贝大小为第三个参数
	// memcpy(buf2,buf1,sizeof(buf1));
	// 如果拷贝的内存大小不是类型大小倍数会导致字节丢失，数据被截取
	memcpy(buf2,buf1,13);
	print(buf2,10);
	//避免如下情况，拷贝内存地址有重叠
	int *start=buf1+1;
	int *end=buf1+3;
	// memcpy(start,end,16);
}
// 数组的移动，和拷贝类似
void move(){
	int buf[10]={1,3,4,4,93,12,323,43};
	int des[5]={0};
	//buf的指针偏移2位作为源地址，要移动到des的内存大小为16个字节，des存放的位置偏移1
	memmove(des+1,buf+2,16);
	print(des,5);
}
int main(int argc, char const *argv[])
{
	void* pa(int,int);//定义一个名为pa的函数，返回值为 void *
	int* (*pb)(int,int );//定义一个指针指向函数，返回类型为int *

	int (*p)(int,int);//定义一个指针指向函数，返回类型为int
	int status=0;
	scanf("%d",&status);
	//在运行时动态的将函数赋给函数指针
	status==0?p=add:p=minus;
	//使用函数指针间接调用函数
	int result=p(3,4);
	printf("%d\n",result );
	int buf[10]={1,2,3};
	//define a pointer to function with return type void 
	void (*p1)(int *p,int);
	p1=print;
	p1(buf,10);
	//使用函数指针作为函数的参数，add称为回调函数
	result=func(add,5,6);
	printf("%d\n", result);

	// reset();
	// copy();
	move();



	return 0;
}