#include <stdio.h>
#define MONTHS 12
#define YEARS 3
//数组的初始化,可以使用下标指定要初始化的元素，如果其后有连续赋值
// 如［4]=31,30,30，表示［5］＝30，［6］＝30，如果有重复赋值，以最后一次为准
void designate(void){
	int months[MONTHS]={30,28,[4]=31,30,30,[1]=29};
	for (int i = 0; i < MONTHS; ++i)
	{
		printf("%2d %d\n", i+1,months[i]);
	}

}

// 数组的边界检查
void bound(void){
	int value1=32;
	int array[MONTHS];
	int value2=134;
	printf("value1=%d value2=%d\n", value1,value2);
	for (int i = -1; i <=MONTHS; i++)
	{
		array[i]=2*i+1;
	}
	//此编译的结果是value1的初始化值被更改
	printf("value1=%d value2=%d\n", value1,value2);
	for (int i = 0; i <MONTHS; ++i)
	{
		printf("%d\n", array[i]);
	}
}



/*
	二维数组
	初始化使用｛｝与不使用的区别
	int[2][3]=｛{2,3},{4,5}｝={{2,3,0},{4,5,0}}
	int[2][3]={2,3,4,5｝={{2,3,4},{5,0,0}}

*/

void rain(void){
	const float rains[YEARS][MONTHS]={
		{1,2,43,23,5,3,23,4,65,76,12,32},
		{1,2,43,23,5,3,23,43,23,5,3,23},
		{23,4,65,76,12,32,43,23,5,3,23,93}};

	for (int i = 0; i < YEARS; ++i)
	{
		float year_sum=0;
		for (int j = 0; j < MONTHS; ++j)
		{
			year_sum+=rains[i][j];	
		}
		printf("year[%d] arv rain drop=%.2f\n",i+1, year_sum/MONTHS);
	}

	for (int i = 0; i < MONTHS; ++i)
	{	
		float month_sum=0;
		for (int j = 0; j < YEARS; ++j)
		{
			month_sum+=rains[j][i];
		}
		printf("month[%d] in three years arv rain drop=%.2f\n",i+1, month_sum/YEARS);

	}
	
}

int sum_arr(int *start,int *end){
	int total=0;
	while(start<end){
		total+=*start;
		start++;
	}
	return total;
}
// 指针运算优先级,*和＋＋具有相同优先级，但*p1++，先指针自增然后取原指针值，＊＋＋p1，指针自增取新指针的值
void point_order(void){
	int data[2]={100,200};
	int moredata[2]={300,400};
	int *p1,*p2,*p3;
	p1=p2=data;
	p3=moredata;
	printf("p1=%d,p2=%d,p3=%d\n",*p1,*p2,*p3 );
	printf("p1++=%d,++p2=%d,(*p3)++=%d\n",*p1++,*++p2,(*p3)++);
	printf("p1=%d,p2=%d,p3=%d\n",*p1,*p2,*p3 );


}
//关于const 与pointer
void ptr_const(void){
	int arr[5]={1,2,3,4,4};
	//指向常量的指针
	const int * p=arr;
	// 不能修改指向的值 *p=23;可以移动p++;

	// 常量指针，只能指向最初的位置
	int  * const p2=arr;
	// 不可移动p2=&arr[2];可以修改指向的数值*p2=100;

	//指向常量的常量指针，既不能移动也不能修改值
	const int * const p3=arr;
	
	int *p4;
	const int *p0;
	p0=p4;
	// p4=p2;不合法常量指针不能赋给非常量指针

	const int **p5;
	int **p6;
	//p5=p6 不合法，在二级指针层面，非常量也不能赋给常量，不安全


	
	
}

void sum_array(int p[][3],int rows){
	int col_sum=0;
	int total=0;
	// int row;
	// int col;
	for (int row = 0; row < rows; ++row)
	{
		int row_sum=0;
		for(int col = 0; col < 3; ++col)
		{
			row_sum+=p[row][col];	
		}	
		printf("row[%d]_sum=%d\n",row,row_sum );	
		total+=row_sum;
	}

	for (int col = 0; col < 3; ++col)
	{
		for (int row = 0; row < rows; ++row)
		{
			col_sum+=p[row][col];
		}
		printf("col[%d]_sum=%d\n", col,col_sum);
	}
	printf("total=%d\n",total );

}
int main(int argc, char const *argv[])
{
	// designate();
	// bound();
	// rain();
	int arr[5]={23,32,43,1,3};
	int result=sum_arr(arr,arr+5);
	printf("the result of sum is %d\n", result);
	point_order();
	ptr_const();
	int arr2[3][3]={{1,2,3},{1,2,3},{1,2,3}};
	printf("%lu,%lu\n",sizeof(arr2),sizeof(arr2[0]));
	sum_array(arr2,3);
	return 0;
}