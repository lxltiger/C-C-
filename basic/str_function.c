#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 81
/*C中字符串的操作  头文件位置/usr/include*/


void diff_point_array(){
	//字符串数组初始化从静态区把字符串复制给数组，array是常量
	 char array[]="come on Everybody";
	// 指向字符串的指针，初始化只是复制字符串的地址，p是变量
	const char *p="Hello Everybody";	
	array[2]='m';//ok
	// 但是，使用指针指向的数组不能通过以下方式修改，如果能编译通过，引用Hello Everybody的字符串都是被修改后的
	// 所以这种形式建议使用const修饰
	// p[2]='l';some fail to compile
}

//字符串数组
void string_array(){
	//char 类型指针数组，每个元素指向一个字符串首地址，
	// array是指针的指针，*(array+1)，array［1］表示取第二个元素地址
	const char *array[3]={"one","two","three"};
	// 打印数组的第一个元素
	printf("%s\n", array[0]);
	// 打印第三个元素指针指向的值
	printf("%c\n", *array[2]);

}
//字符串的复制只是复制了地址
void string_copy(){
	 char * s1="hei mr DJ";
	char * s2=s1;
	printf("%15s %15s %15s\n", "指针的值" ,"字符串值" ,"指针地址");
	printf("%p %s %p\n", s1,s1,&s1);
	printf("%p %s %p\n", s2,s2,&s2);

}
// get获取键盘的输入，读到第一个换行符为终止，丢弃换行符，然后添加'\0'结尾，
// 不检查存储空间是否容纳输入长度，容易溢出，不安全
void string_get(){
	// 分配空间
	char s[11];
	char *ptr;
	// 将标准输入的字符串放入数组，超出部分会溢出到其他空间
	//如果正常返回字符串的指针，否则返回NULL
	// ptr=gets(s);
	// printf("you input %s，aha it‘s %s\n", s,ptr);

	char input[51];
	//只要输入正常
	while(gets(input)){
		if(strcmp("q",input)==0){
			break;
		}
		printf("your input is %s,type q to exit\n", input);
	}

	//以下都是判断读取字符结尾，NULL和EOF值都是0，但前者是地址，后者是字符
	// while(gets(name)!=NULL)
	// while((ch=getchar())!=EOF)
}

/*
*fgets相比gets更安全，主要针对文件操作
＊第二个参数max为最大读入字符数，可读入max－1个字符加‘\0’结束符，或者读到‘\0’结束，读到换行符并不丢弃
＊第三个参数为输入原，stdin表示键盘
**/
void string_fgets(void){
	char array[MAX];
	char *ptr;
	printf("%s\n", "please enter your name");
	ptr=fgets(array,10,stdin);
	printf("%s ah your name is %s\n", array,ptr);
}
//scanf 与gets相比是用来读单词的，以两种方式结束录入，读到第一个空白字符，读到指定长度
void string_scanf(void ){
	char name1[11],name2[11];
	printf("please enter two names,split with space\n");
	//第一个名字最长5个字符，第二个10个字符，如果是lxltiger hehiehi,name1=lxlti ，name2=ger
	// 一个UTF－8中文字符相当三个英文字符,&name1[3]表示从索引为3的位置开始写入而不是开始
	int count=scanf("%5s %10s",name1,name2);
	printf("name1=%s,name2=%s\n", name1,name2);

}
//puts函数以地址作为参数，遇到结束符停止（如果没有会继续在内存中读取），自动添加换行符，
void put_out(void){
	char array[MAX]="array is initialized to me";
	const char *p="a pointer was initialized to me ";
	// 更改字符为结束符
	array[5]='\0';
	puts(array);
	// 从索引为6的位置开始输出
	puts(&array[6]);
	
	puts(p);
	puts(p+3);

}
//面向文件的puts，第二个参数指定文件，stdout为屏幕，不添加换行符
void fput_out(void){
	char array[MAX];
	while(fgets(array,MAX,stdin)){
		fputs(array,stdout);
	}
}
//不输出换行符的puts
void string_puts1(const char *string){
	while(*string){
		putchar(*string++);
	}
}
//输入字符添加换行符并返回字符数的put
int string_puts2(const char *string){
	int count=0;
	while(*string){
		putchar(*string++);
		count++;
	}
	putchar('\n');
	return count;
}

//把第二个字符串加到第一参数上，不检查第一个参数能否容纳
void string_cat(void){
	char name[80];
	char add[]=" is good";
	gets(name);
	strcat(name,add);
	printf("%s\n", name);
}
//可以指定最多添加的字符数
void string_ncat(){
	char name[20];
	char add[]="is wonderful baby hei hei hei";
	printf("what is name \n");

	fgets(name,sizeof(name),stdin);
	//最多可添加的字符数
	int available=sizeof(name)-strlen(name)-1;
	printf("available=%d\n", available);
	strncat(name,add,available);
	puts(name);
}
//字符串的比较
void string_cmp(void){
	char array[MAX];
	fgets(array,MAX,stdin);
	// fgets添加换行符，先如此比较
	while(strcmp("lxltiger\n",array)!=0){
		puts("guess again ");
		fgets(array,MAX,stdin);
	}
	puts("you are right ");

}

//以指定字符串结束输入
void quit_chk(void){
	int limit=100;
	char array[limit][MAX];
	char stop[]="quit";
	int row_write=0;
	puts("type something end with quit");
	// 如果什么都不输入直接按enter键退出array[row_write][0]='\0'
	while(row_write<limit&&gets(array[row_write])!=NULL&&
		strcmp(stop,array[row_write])!=0){
		row_write++;
	}
	printf("you write %d rows \n", row_write);
}
// 带参数的字符串比较
void string_ncmp(void){
	//最好加上const修饰，数组包含的是指针，对字符串的修改会影响其他引用
	const char *arr[3]={"lxltiger","lxl839232","ltgasdad"};

	int count=0;
	for (int i = 0; i < 3; ++i)
	{
		if(strncmp("lxl",arr[i],3)==0){
			count++;
		}
	}
	printf("%d chars starts with lxl \n",count);

}
// 字符串的复制,不安全
void string_cpy(void){
	int limit=20;
	char content[limit][MAX];
	char temp[MAX];
	int line=0;
	while(line<limit&&gets(temp)){
		if(temp[0]=='q'){
			break;
		}
		strcpy(content[line],temp);
		line++;
	}
	puts("here is the word accepted");
	for (int i = 0; i < line; ++i)
	{
		puts(content[i]);
	}

}

void string_ncpy(void){
	int limit=5;
	int size=10;
	char buffer[limit][size];
	int line=0;
	char temp[20];
	while(line<limit&&gets(temp)){
		if(strncmp("quit",temp,4)==0){
			break;
		}
		//复制buffer［line］最多能容纳的字符数（除空字符）
		strncpy(buffer[line],temp,size-1);
		// 最后一个字符为空字符
		buffer[line][size-1]='\0';
		line++;
	}
	puts("the content in buffer ");
	for (int i = 0; i < line; ++i)
	{
		puts(buffer[i]);

	}
}

// sprintf 把字符串合并成格式化字符串 在stdio.h

void string_sprintf(void){
	int size=20;
	char firstName[size];
	char lastName[size];
	float price=0;
	char total[MAX];
	puts("please enter you firstName lastName price in way like this Jask Smith 32424");
	int result=scanf("%s %s %f",firstName,lastName,&price);
	if(result==3){
		sprintf(total,"%s,%-19s %6.2f",lastName,firstName,price);
		puts(total);
	}else{
		puts("something wrong");
	}
}

// 用冒泡排序将输入的字符串排序输出
void string_sort(void){
	int limit=10;
	char input[limit][MAX];
	char *strs[limit];
	int line=0;
	while(line<limit&&gets(input[line])!=NULL&&input[line][0]!='\0'){
		strs[line]=input[line];
		line++;
	}

	for (int i = 0; i < line; ++i)
	{
		for (int j = i+1; j < line; ++j)
		{
			if(strcmp(strs[i],strs[j])>0){
				char *temp=strs[i];
				strs[i]=strs[j];
				strs[j]=temp;
			}
		}
	}
	for (int i = 0; i < line; ++i)
	{
		puts(strs[i]);
	}
}
// 转换字符大小写，需要逐个字符处理
void string_case(void ){
	char buffer[]="you arE the one";
	int len=strlen(buffer);
	for (int i = 0; i < len; ++i)
	{
		buffer[i]=toupper(buffer[i]);
	}
	
	puts(buffer);

}
int main(int argc, char const *argv[])
{
	// diff_point_array();
	// string_array();
	// string_copy();
	// string_get();
	// string_fgets();
	// string_scanf();
	// put_out();
	// fput_out();
	// string_puts("you are the one");	
	// printf("I count %d character\n",string_puts2("the sentence I count ") );
	// string_cat();
	// string_ncat();
	// string_cmp();
	// quit_chk();
	// string_ncmp();
	// string_cpy();
	// string_ncpy();
	// string_sprintf();
	// string_sort();
	string_case();

	return 0;
}
void one(){
	char buf[100]="miss you baby";
	char *p=buf;
	// 从当前指针位置向前移动3个
	p+=3;
	//字符串的输出是从指针的位置到结尾
	printf("%s\n", p);
}
//argc表示参数的个数 argv是char类型指针数组，表示参数的内容
void two(int argc,char const *argv[]){
	if(argc<=1){
		printf("%s\n","not valid param");
		return ;
	}
	char buf[100]="ls";

	for (int i = 1; i < argc; ++i)
	{
		strcat(buf," ");
		strcat(buf,argv[i]);
	}
		printf("%s\n", buf);

	system(buf);
}
void three(void){
	char ch;
	printf("please enter some character \n");
	while((ch=getchar())!='#'){
		// 如果什么都没输只会车继续循环读取
		if('\n'==ch)
			continue;
		if(islower(ch)){
			switch(ch){
				case 'a':
				printf("aaaa\n");
				break;
				case 'b':
				printf("bbbb\n");
				break;
				default:
				printf("nothing\n");
			}
		}else{
			printf("it's not a lowercase character\n");
		}
		//如果输入的不是一个字符而是字符串，只取第一个，其余的舍弃, 否则会虚幻判断
		while(getchar()!='\n'){
			continue;
		}
	}
}
//使用main函数的参数做一个四则运算的计算器
int main(int argc, char const *argv[])
{
	// two(argc,argv);
	// three(argc,argv);
	if(argc<4){
		printf("%s\n", "至少需要4个参数");
		return -1;
	}
	// 如果乘法不用\*打印结果是a.c
	printf("operator is %s %lu\n", argv[2],strlen(argv[2]));
	if(strlen(argv[2])!=1){
		printf("%s\n", " 操作符不正确");
		return -1;
	}
	int one=atoi(argv[1]);
	int two=atoi(argv[3]);
	int result=0;
	//参数的输入如 ./char 22 / 4，但在输入*时需要\*转义
	switch (argv[2][0]){
		case '+':result=one+two;break;
		case '-':result=one-two;break;
		case '*':result=one*two;break;
		case '/':
		if(two!=0){
			result=one/two;
		}else{
			printf("%s\n", "devider cannot be 0");
			return -1;
		}
		break;
		default :
		printf("%s\n", "unknown operator");
		return -1;

	}
	
	printf("%d%s%d=%d\n", one,argv[2],two,result);


	return 0;
}
	/* 操作字符串的函数*/
int main1(int argc, char const *argv[]){
	char buffer[100]={0};
	//scanf获取用户键盘录入，以回车或空格为结束标记,所以空格后的字符串不能显示，
	// 它是不安全的，键盘录入的长度可能超过缓冲导致溢出
	scanf("%s",buffer);
	printf("%s\n", buffer);
	//gets()函数只以回车为结束标记，解决了空格问题，但依然存在溢出问题，而且只能处理字符数组
	gets(buffer);
	printf("%s\n", buffer);
	return 0;
}

int main2(int argc, char const *argv[])
{
	char buffer[10]={0};
	//数组的长度此时为10
	printf("数组的大小为%d\n",sizeof(buffer));
	// 字符长度，此时为0，结束符不会计入，所以字符串长度最大为数组长度－1
	printf("字符串长度为%d\n",strlen(buffer));
	// fgets函数增加了要打印字符数组长度的参数，一定程度上是安全的，因为最后一个字符是0，所以实际输出比数组大小要少一位
	fgets(buffer,sizeof(buffer),stdin);
	//如果键盘录入比数组长度小，换行符\n也是会加上的
	printf("接受键盘输入后字符串长度为%d\n",strlen(buffer));
	for (int i = 0; i < strlen(buffer); ++i){
		printf("%d\n", buffer[i]);
	}
	// 设置索引为5的字符为结束标记'\0',其assic码为0，字符‘0’的assic码为48
	buffer[5]='\0';
	printf("%s\n", buffer);
	//puts（str）函数只打印字符串并换行
	puts(buffer);
	//上述函数的文件操作版,不换行
	fputs(buffer,stdout);
	// 字符串结束符后面的字符都不再属于这个字符串数组
	printf("插入结束符0后字符串长度为%d\n",strlen(buffer));

	
	return 0;
}


int main3(int argc, char const *argv[])
{
	char c1[50]="worldwonderful"	;
	char c2[]="123worldz";
	// 将第二个字符串追加到第一个上，可能导致溢出
	strcat(c1,c2);
	printf("%s\n", c1);
	//添加第二个字符串指定数目到第一个字符串上
	strncat(c1,c2,2);
	puts(c1);
	//比较两个字符串是否形同，返回0表示相同
	int result=strcmp(c1,c2);
	printf("%d\n",result);
	//比较字符串指定长度是否相等
	int result2=strncmp(c1,c2,5);
	printf("%d\n", result2);
	//将第二个字符串复制到第一个中，第一个会被清空，可用于给字符数组赋值
	// strcpy(c1,c2);
	// puts(c1);
	//将制定长度复制过去，第一个不会清空，长度的字符被覆盖
	strncpy(c1,c2,4);
	puts(c1);
	return 0;
}

int main4(int argc, char const *argv[])
{
	char buffer[20]="12we";
	//将整数型字符串转化成整数，开头必需是数组，否则为0;相同的有转浮点atof，转长整形aotl
	int number=atoi(buffer);
	printf("%d\n", number);
	char buffer2[20]={0};
	//将格式化字符串结果输出到制定字符数组而不是控制台
	sprintf(buffer2,"the result of transfer is %d",number);
	printf("%s\n", buffer2);
	//将整数转化成字符串
	sprintf(buffer2,"%d",299);
	printf("%s\n", buffer2);

	return 0;
}

int main5(int argc, char const *argv[])
{
	char buffer[20]="abc=100";
	int number;
	//从字符串获取输入
	sscanf(buffer,"abc=%d",&number);
	printf("the number is %d\n", number);
	char buffer2[20]="11+22";
	int a;
	int b;
	sscanf(buffer2,"%d+%d",&a,&b);
	printf("the result of %s is %d\n",buffer2,a+b);
	return 0;
}

int main(int argc, char const *argv[])
{
	char buffer[20]="hello world";
	//把查找到的字符到结尾返回给指针，如没有返回null
	const char *buf=strchr(buffer,'l');

	printf("%s\n", buf);
	//查找制定字符串，返回找到的字符串及结尾
	buf=strstr(buffer,"wor");
	printf("%s\n", buf);

	//重新赋值
	strcpy(buffer,"hei_duang_qiu");
	//使用指定分割符切割字符串
	buf=strtok(buffer,"_");
	while(buf){
		printf("%s\n", buf);
		//继续分隔，如果没有返回null，也就是0
		buf=strtok(NULL,"_");
	}

	strcpy(buffer,"32341034");
	int len=strlen(buffer);
	//一定要赋值初始化
	int total=0;
	for (int i = 0; i < len; ++i)
	{
		int num=buffer[i]-'0';
		printf("num=%d\n", num);
		int param=1;
		for (int j = 0; j < len-i-1; ++j)
		{
			param=param*10;
		}
		total=total+num*param;

	}
	printf("%d\n", total);

	return 0;
}





