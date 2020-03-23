#include <stdio.h>

/*指针数组*/


void  one(){
	//定义一个指针数组，每个成员都为int *
	int *p1[10];
	//数组的在内存大小，和数组元素占内存的大小，不论指针类型，都是一样的，32位 4个字节，64位8个字节
	printf("%lu,%lu\n", sizeof(p1),sizeof(p1[0]));

	 int a=10;
	 int b=20;
	 p1[0]=&a;
	 p1[1]=&b;

	 //定义一个二维数组的指针，它指向int［3］这种类型
	 int(*p)[3];
	 int buf[2][3]={{1,3,4},{3,4,5}};
	 // p指向了二维数组的第一行
	 p=buf ;
	 // p[0],*p,*(p+0)都表示0行0列元素的地址
	 // p+1第一行首地址
	 // *(p＋1) p[1]都表示1行0列元素地址
	 // p[1]+2, *(p+1)+2,&p[1][2] 都表示1列2元素地址
	 // *(p[1]+2),*(*(p+1)+2),p[1][2] 都表示1列2元素的值
	 printf("%lu\n", sizeof(p));
	 //位移了sizeof（int［3］）＊1
	 printf("%p,%p\n", p,p+1);
	 //使用指针遍历二位数组
	 for (int i = 0; i < 2; ++i)
	 {
	 	//打印每行的首地址
	 	printf("第%d行首地址%p\n",i, p+i);
	 	// printf("第%d行首地址%p\n",i, *(p+i));
	 	for (int j = 0; j < 3; ++j)
	 	{
	 		// printf("%d\n", p[i][j]);
	 		printf("第%d行第%d值%d\n",i,j, *(*(p+i)+j));

	 	}
	 }
}
//求二维数组的横纵平均值
void two(){
	int array[3][4]={{1,3,4,5},{2,3,45,4},{2,3,4,5}};
	int(*p)[4]=array;
	//求横行的平均值
	for (int i = 0; i < 3; ++i)
	{
		float sum=0;
		for (int j = 0; j < 4; ++j)
		{
			sum+=*(*(p+i)+j);
		}
		printf("row%d,average is %f\n",i, sum/4);

	}

	//求列的平均值
	for (int i = 0; i < 4; ++i)
	{
		float sum=0;
		for (int j = 0; j < 3; ++j)
		{
			sum+=*(*(p+j)+i);
		}
		printf("column%d,average is %f\n",i, sum/4);

	}

}
//二位数组作为形参的表现方式, 不灵活，列数限死了
void three(int (*p)[4],int width,int height){
	printf("%d,%d\n", width,height);
}

// 返回值为指针的函数
char *mystrchr( char *p,char c){
	while(*p){
		//如果找到返回当前指针
		if(*p==c){
			return p;
		}
		p++;
	}
	return NULL;
}

// 如果指针只用来读取，或不希望指针内容被修改，使用const修饰 
int main(int argc, char const *argv[])
{
	// one();
	// two();
	int array[3][4]={{1,3,4,5},{2,3,45,4},{2,3,4,5}};
	int(*p)[4]=array;
	// three(array,sizeof(array[0])/sizeof(int),sizeof(array)/sizeof(array[0]));

	char buf[100]="hello lxl";
	// 使用自定义函数查找字符并返还字符的指针地址
	char *p2=mystrchr(buf,'l');
	printf("%s\n", p2);

	int array2[6]={2,9,4,5,9,6};
	submax(array2,sizeof(array2)/sizeof(int));
	
	
	return 0;
}