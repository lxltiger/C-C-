#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TITLE 41
#define MAX_AUTHOR 31

#define LEN 31
struct names
{
	/* data */
	char first[LEN];
	char second[LEN];

};

struct guy
{
	/* data */
	struct names handler;
	char job[LEN];
	int salary;
};

int main(int argc, char const *argv[])
{
	/* 指针和结构体 */
	struct guy college[2]={
		{
			{"tim","wang"},
			"android",
			8000
		},
		{
			{"Jack","chen"},
			"ios",
			129323
		}
	};
	// temp指向结构的指针,一个结构体的名字不是其地址
	struct guy *temp=&college[0];

	printf("guy one %s income is %d\n",temp->handler.first,(*temp).salary );
	temp++;
	printf("guy two %s income is %d\n",temp->handler.second,temp->salary);




	return 0;
}
/*结构的嵌套*/
struct name 
{
	/* 姓名的结构体 */
	char firstName[LEN];
	char lastName[LEN];

};
/*结构体名不要和文件重名*/
struct friends
{
	/* 好友结构体 */
	struct name handler;
	char job[LEN];
	char mob[LEN];

};

int main(int argc, char const *argv[])
{
	/* code */
	struct friends allen={
		{"Tom","allen"},
		"engineer",
		"13832328383"
	};

	printf("My friend %s,working as %s.His mobile phone num is %s\n",
		allen.handler.firstName, allen.job,allen.mob);
	return 0;
}

struct book
{
	/* 描述一本书的结构体 */
	char title[MAX_TITLE];
	char author[MAX_AUTHOR];
	float value;
};

// 剔除字符串结尾的换行符
void trim(char *origin){
	char *found=strchr(origin,'\n');
	if(found){
		*found='\0';
	}

}
int main1(int argc, char const *argv[])
{
	// 声明结构体变量
	struct book library;
	puts("please enter the name of book");
	// 获取书名，含换行符
	fgets(library.title,MAX_TITLE,stdin);
	// 去除换行符
	trim(library.title);
	puts("enter the author of book");
	fgets(library.author,MAX_AUTHOR,stdin);
	trim(library.author);
	puts("the price of book");
	int status=0;
	// 获取书价,scanf函数忽略空格和换行符
	while((status=scanf("%f",&library.value))!=1){
		puts("the price is not right,inputs like 23.32");
		// 去除缓存中其它字符，否则会无限循环
		scanf("%*s");

	}
	// 如果还有外层循环，此处还要去除 scanf忽略的其它字符
	printf("the name of book is %s,the author is %s,price is %.2f\n",library.title,library.author,library.value);

	// 结构体的声明及初始化
	struct book gift={.title="hei",.author="Alex",.value=23.33};
	printf("the name of book is %s,the author is %s,price is %.2f\n",gift.title,gift.author,gift.value);

	return 0;
}
//说明了一个数据结构体的数据类型
struct student {
	char name[100];
	int age;
	int gender;
};



void one(void){
	//声明一个student结构体变量
	struct student st;
	//给变量成员变量赋值
	strcpy(st.name,"lxl");
	st.age=23;
	st.gender=2;
	printf("name=%s,age=%d,gender=%d\n", st.name,st.age,st.gender);
}
void two(void){
	struct student st={"lyh",13,1};

	printf("name=%s,age=%d,gender=%d\n", st.name,st.age,st.gender);

}
void three(void){
	//无序初始化
	struct student st={.name="lxlslkdl",.gender=21,.age=33};
	printf("name=%s,age=%d,gender=%d\n", st.name,st.age,st.gender);

}
void four(void){
	//全部初始化为0
	struct student st={0};
	scanf("%s",st.name);
	scanf("%d",&st.age);
	scanf("%d",&st.gender);
	printf("name=%s,age=%d,gender=%d\n", st.name,st.age,st.gender);


}

//会以最大元素大小作为对齐单位，并且偶数对齐，正确的配置变量位置可节约内存	
struct A{
	long long c;
	char a;
	char b;
};
void five(void){
	struct A a;
	printf("%lu\n", sizeof(a));
}
struct B{
	char a:2;//定义一个插入类型的变量a，但只有2个位
	char b:4;//同上，只用四位，不能超过数据类型大小上限，如9就会报错
};
void six(void){
	struct B b;
	b.a=3;//只有2位，二进制表示为11，高位为符号位，结果为－1
	b.b=16;//只有4位，二进制表示为10000，截取后四位，结果为0
	printf("the size of struct using bit is %lu byte,b.a=%d,b.b=%d\n", sizeof(b),b.a,b.b);
}
struct C{
	char a;
	char b;
	char c;
};

void seven(void){
	struct C c;
	char *p=(char *)&c;
	p[0]='a';
	p[1]='b';
	p[2]=65;
	printf("%c,%c,%c\n", c.a,c.b,c.c);
}
struct Worker
{
	char name[10];
	unsigned char age;
	unsigned char score;
	char title[20];
};

void eight(void ){
	struct Worker worker[3]={{"one",23,34,"boss"},{"two",24,42,"worker"},{"three",43,23,"man"}};
	for (int i = 0; i < 3; ++i)
	{
		printf("name=%s,age=%d,score=%d,title=%s\n",
			worker[i].name,worker[i].age,worker[i].score,worker[i].title );
	}
}
void swap(Worker *w1,Worker *w2){
	Worker temp=*w1;
	*w1=*w2;
	*w2=temp;
}
//给结构体排序，以Worker为例，按年龄从小到大，相等的比较score
void sortStruct(void){
	struct Worker worker[5]={{"one",23,34,"boss"},
		{"two",94,42,"worker"},
		{"three",43,93,"man"},
		{"李晓林",53,23,"duang"},
		{"李元昊",43,83,"hei"}};
	for (int i = 0; i < 5; ++i)
		{
			for (int j = i+1; j < 5; ++j)
			{
				if(worker[i].age>worker[j].age)	{
					swap(&worker[i],&worker[j]);
				}else if(worker[i].age==worker[j].age){
					if(worker[i].score<worker[j].score)	{
					swap(&worker[i],&worker[j]);

					}
				}
			}
		}	

	for (int i = 0; i < 5; ++i)
	{
		printf("name=%s,age=%d,score=%d,title=%s\n",
			worker[i].name,worker[i].age,worker[i].score,worker[i].title );
	}
}

//使用指针给结构体赋值
void ten(void){
	struct Worker w={0};
	struct Worker *temp=&w;
	// temp->name="dung";
	strcpy(temp->name,"duang");
	temp->age=32;
	temp->score=53;
	strcpy(temp->title,"boss");
	
	printf("name=%s,age=%d,score=%d,title=%s\n",
			w.name,w.age,w.score,w.title );
}
void eleven(void){

}
int main(int argc, char const *argv[])
{
	// one();
	// two();
	// three();
	// four();
	// five();
	// six();
	// seven();
	// eight();
	// sortStruct();
	ten();


	





	
	return 0;
}