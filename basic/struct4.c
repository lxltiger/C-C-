#include <stdio.h>
#include <string.h>
#define MAX 41


struct name
{
	/* data */
	char last[MAX];
	char first[MAX];
	int length;
};


void getInfo(name *anyName){
	puts("enter you first name");
	gets(anyName->first);
	puts("enter you last name");
	gets(anyName->last);

}

void makeInfo(name *anyName){
	anyName->length=strlen(anyName->last)+strlen(anyName->first);
}

void showInfo(const name *anyName){
	printf("fist name %s last name %s ,the total length is %d\n",anyName->first,anyName->last,anyName->length );
}

/*使用结构体作为返回值*/
struct name getInfo2(void){
	struct name temp;
	puts("enter you first name");
	gets(temp.first);
	puts("enter you last name");
	gets(temp.last);

	return temp;
}
/*使用结构体作为参数和返回值*/
struct name makeInfo2(name temp){
	temp.length=strlen(temp.first)+strlen(temp.last);
	return temp;
}

void showInfo2(name temp){
	printf("fist name %s last name %s ,the total length is %d\n",temp.first,temp.last,temp.length );
}

	/*  结构体地址和结构体作为参数的比较 */
int main(int argc, char const *argv[])
{
	struct name tom;
	// 使用地址作为参数，节省时间和空间，不会复制结构体，但可能修改原数据导致意外
	getInfo(&tom);
	makeInfo(&tom);
	showInfo(&tom);
	// 使用结构体本身作为参数，每个形参都是副本，会有许多复制，但不会影响原数据，早起C版本不支持
	struct name tim;
	tim=getInfo2();
	// 可以这样给结构体赋值
	tim=makeInfo2(tim);
	showInfo2(tim);

	return 0;
}