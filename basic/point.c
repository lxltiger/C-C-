#include <stdio.h>
#include <string.h>

void one()
{
	int num=10;
	//&是取变量地址的意思
	printf("the address of num is %p\n", &num);
	
	//将num地址赋值给变量p
	int *p=&num;
	//定义一个变量p1,它可以指向一个int的地址，*p意思是指针变量指向内存的内容
	int *p1;
	//赋值和定义分开
	p1=&num;
	// 打印指针地址和其代表的内容
	printf("the address of num is%p,the content of point is %d\n", p,*p);
	
	*p=20;
	printf("change the value of num by point %d\n", num);

	//数组的地址和其第一个元素地址相同，元素地址的间隔与元素类型相关
	char buf[10];
	// char占一个字节，所以0x7fff53ac1c7e,0x7fff53ac1c7f
	printf("the address of buf %p,%p,%p\n",buf,&buf[0],&buf[1]);
	int buf2[10]	;
	// int 占4个字节，所以元素地址之间的距离就是4，0x7fff53ac1c50,0x7fff53ac1c54
	printf("the address of buf2 %p,%p,%p\n",buf2,&buf2[0],&buf2[1]);
	//不指向任何数据类型的无类型指针
	void *p3;
	//指向NULL的为空指针
	p3=NULL;
	// 指针在32位操作系统下就是32位的整数,64就是64位整数，与指向的数据类型无关
	printf("%d,%d,%d\n",sizeof(p),sizeof(p1),sizeof(p3));

	int *p4;
	//如果不把变量地址赋给指针,就给指针指向的地址赋值会导致错误，这就是野指针，是非法的，空指针是合法的
	// p4=&num;
	// *p4=1;
}

void two()
{
	int a=0x1234;
	char *p=(char *)&a;

	
	char buf[10] = { 0x12, 0x34, 0x56, 0x78, 5, 6, 7, 8, 9, 10 };
	//使用强制转化
	int *p2=(int *)buf;
	// 使用的是小段对齐，0x12345678在内存中是78，56，34，12放置
	// 所以p2强转int类型占4个字节，结果是0x78563412；
	printf("%#x\n", *p2);
	//指针 移动4个字节
	p2++;
	printf("%#x\n", *p2);
}

//常量指针和指针常量
void three()
{
	int a=10;
	// 定义一个指针常量，只能读和指向
	const int *p=&a;
	//不能更改内容
	// *p=29;
	a=20;
	printf("%d\n", *p);
	int b=435;
	//重新指向
	p=&b;
	printf("%d\n", *p);
// 定义一个常量指针，能赋值，但不能重指向
	int *const p1=&a;
	// 重新赋值
	*p1=40;
	//不能重指向
	// p1=&b;
	printf("%d\n", *p1);

}
//打印工具栏
void print(char buf[]){
	// int len=strlen(buf);
	int len=sizeof(buf);
	printf("%d\n", len);
	for (int i = 0; i < 10; ++i)
	{
		printf("buf[%d]=%d\n",i, buf[i]);
	}
}
// 指针和数组的关系
void four()
{
	char buf[10]={1,3,4,5};
	print(buf);
	// 指向数组的首地址，也可以
	// char *p=buf+1 指向第二个
	char *p=buf;

	for (int i = 0; i < 10; ++i)
	{
		*p=10*i;
		//移动指针
		p++;
	}
	print(buf);
	//重新指向首地址
	p=buf;

}

void five(){
	char buf[40]="134.32.2.121";
	int a=0;
	int b=0;
	int c=0;
	int d=0;
	sscanf(buf,"%d.%d.%d.%d",&a,&b,&c,&d);
	printf("a=%d,b=%d,c=%d,d=%d\n",a,b,c,d);
	
}
void six(){
	char buf[20]="hello";
	char buf2[20]="world";
	char *p=buf;
	char *p2=buf2;
	int len=0;
	// 通过指针求数组长度
	while(*p){
		p++;
		len++;
	}
	while(*p2){
		//与以下三行效果相同
		// *p++=*p2++;
		*p=*p2;
		p++;
		p2++;
	}
	printf("the length of buf %d\n", len);
	printf("%s\n", buf);
	//int类型指针可以通过下标来偏移，字符数组不行
	int temp[10]={20,1,23,43};
	int *p3=temp;
	// p3[2], ＊（p3+2）, temp[2]意思相同
	printf("指针可以下标%d\n", p3[2]);

}
//求第二大
void  seven(int *p,int len){
	//指针冒泡排序
	// int *p=array;
	int max=0;
	int second=0;
	if(*p>*(p+1)){
		max=*p;
		second=*(p+1);
	}else{
		max=*(p+1);
		second=*(p);
	}

	p++;
	for (int i = 2; i < len; ++i)
	{
		p++;
		//如果找到更大的，重新排名
		if(*p>max){
			second=max;
			max=*p;

		}else if(*p>second){
			second=*p;
		}
	}
	printf("%d %d\n", max,second);

}

//冒泡排序
void sort(int *p,int len){

	for (int i = 0; i < len; ++i)
	{
		for (int j =1; j < len-i; ++j)
		{
			if(*p<*(p+j)){
				int temp=*p;
				*p=*(p+j);
				*(p+j)=temp;
			}
		}
		p++;
	}
}
void print(int array[],int len){
	for (int i = 0; i < len; ++i)
	{
		printf("%d>", array[i]);
	}
	printf("\n");
}
//逆转数组
void converse(int *p,int len){

	for (int i = 0; i < len/2; ++i)
	{
		int temp=*(p+i);
		*(p+i)=*(p+len-i-1);
		*(p+len-i-1)=temp;
		
	}
}
void converse3(int *p,int len)
{
	int *end=p+len-1;
	int temp=0;
	while(p<end){
		temp=*p;
		*p=*end;
		*end=temp;
		p++;
		end--;
	}

}
// 逆转汉字，每个汉字三个字节，只能处理全汉字
void converse2(char *start,char *end,int len){
	// 0-6 1-5 2-4 3-3
	while(start<end)
// for (int i = 0; i < len/6; ++i)
	{
		
		for (int j = 0; j < 3; ++j)
		{
			char temp=*(start+j);
			*(start+j)=*(end+j);
			*(end+j)=temp;
		}
		start+=3;
		end-=3;
		printf("%p,%p\n", start,end);

	}

}
int main(int argc, char const *argv[])
{
	// one();
	// two();
	// three();
	// four();
	// five();
	// six();
	
	int array[]={-1,-122,5,329,6,-232,-3,9};
	int len=sizeof(array)/sizeof(array[0]);
	converse3(array,len);
	print(array,len);

	return 0;

	// 求第一第二大值
	seven(array,len);
	// 冒泡排序
	sort(array,len);
	print(array,len);
	converse(array,len);
	print(array,len);

	char buf[100]="有朝一日龙得水";
	 len=strlen(buf);
	converse2(buf,&buf[len-3],len);
	printf("%s\n", buf);


	return 0;
}