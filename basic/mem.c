#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//有一个int 类型变量在其它文件已经声明定义，直接使用？？
extern int age;

//static 修饰的为静态变量，只初始化一次，在程序运行期间都存在
void mystatic(){
	static int a=0;//这句运行期间只执行一次
	printf("a=%d\n", ++a);
}

//避免返回栈内存地址
int* getPoint(){
	int a=10;
	return &a;
}
//可以通过函数返回堆地址，但要释放
int* get2(){
	int *p=(int *)malloc(sizeof(int));
	return p;
}

//因为静态变量的生命周期和应用一样长，所指向的地址长期有效，所以可以返回
int* get3(){
	static int x=10;
	return &x;
}

//形参是放在栈区的，方法结束就释放了，此种方式申请的堆内存，没有指针指向
void get4(int *p){
	printf("get4 %p\n", &p);
	p=(int *)malloc(sizeof(int)*10);
	
}

void get5(int **p){
	*p=(int *)malloc(sizeof(int)*10);
	
}

void print(int *p,int count){
	for (int i = 0; i < count; ++i)
	{
		printf("p[%d]==%d\n", i,p[i]);
	}
}
/**
* 内存四区
  代码区：程序被操作系统加载到内存，所有可执行代码加载到代码区，运行时是不变的 
＊静态区：全局变量和静态变量都存在静态区，函数在代码区
* 栈区：栈是一个先进后出的内存结构，局部变量（int a）、函数形参在栈区，当作用域结束自动弹出，
*/
int main(int argc, char const *argv[])
{
	register int a=10;//如果有寄存器空闲，建议放在寄存器使用
	// int *p=&a; 寄存器是没有内存地址的,如果取寄存器类型变量地址可能会出错
	
	for (int i = 0; i < 10; ++i)
	{
		mystatic();

	}
	//在这个方法中返回的是自动变量的临时栈地址，当方法结束就是无效地址，可能会出问题，避免使用
	int *p=getPoint();
	*p=20;
	printf("%d\n", *p);

	//栈区数组，如果过大会导致栈溢出
	int array[100]={0};
	//手动在堆区申请10个int类型的内存空间，maclloc方法返回的是无类型指针
	int *p2=(int *)malloc(10*sizeof(int));
	//初始化
	memset(p2,0,sizeof(int)*10);
	// 可以像数组一样赋值
	for (int i = 0; i < 10; ++i)
	{
		p2[i]=i;
	}
	print(p2,10);
	//需要手动释放
	free(p2);

	char *p3=(char *)malloc(10*sizeof(char));
	free(p3);

	// 使用函数创建堆内存
	int *p4=get2();
	*p4=100;
	printf("%d\n", *p4);
	free(p4);
	
	int *p5=NULL;
	// 传递给函数的是p5的值NULL，而不是引用，可以打印实参和形参，地址不一样
	// get4(p5);
	/*get5(&p5);
	p5[0]=1;
	p5[1]=2;
	printf("%d %d\n", p5[0],p5[1]);*/
	
	int b=10;
	int *p6=&b;
	printf(" p6=%p,%p\n", &p6,p6);
	get4(p6);

	int i=0;
	// scanf("%d\n",&i);
	//可以在堆上动态的创建数组大小,操作系统分配的内存是按默认页大小（4k）来分配的
	/*int *array=malloc(sizeof(int)*i);
	free(array);*/
	//malloc分配的内存没有初始化
	// int *p=(int *)malloc(sizeof(int)*10);
	// calloc分配的内存已初始化
	int *p=(int *)calloc(10,sizeof(int));
	//如果p空间不够用，想从新扩展为20个连续字节的大小，需要用realloc来重新分配，
	// 如果原来的地址不能连续分配会重新分配新内存，并将原来的内存拷贝过来，但其和malloc一样，只分配不初始化
	int *p2=(int *)realloc(p,20);

	for (int i = 0; i < 20; ++i)
	{
		printf("%d\n", p[i]);
	}
	// 如果是重新分配的，需要释放新指针指向的内存
	free(p2);
	// free(p);
	return 0;
}