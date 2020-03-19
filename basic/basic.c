#include <stdio.h>
#include <string.h>
//定义宏常量，常量名大写,include 和define都是文本内容的替换
#define MAX 10
#define NAME "李晓林"

//定义一个指向unsigned char 类型的指针
typedef unsigned char *byte_point;

//参数为 一个字节序列的地址，及字节数
void show_byte(byte_point one,int length){
	for (int i = 0; i < length; ++i)
	{
		// 以十六进制打印这个字节代表的整数，格式为至少两位
		printf("%.2x ", one[i]);
	}
	printf("\n");
}
// 打印一个整数每个字节代表的数, 
// 使用强制类型转换，每种指针都以byte_point类型对待，但不会改变指针本质
void show_int(int x){
	show_byte((byte_point)&x,sizeof(int));

}
//打印指针地址每个字节代表的数
void show_point(void *x){
	show_byte((byte_point)&x,sizeof(void *));

}
// 一个位与1异或就是取反，与0异或就是自己，自己异或自己为0
	// a^1=~a ,a^0=a, a^a=0
void show_mask(void ){
	int x=0x87654321;
	//取最低有效字节
	printf("%#x\n", x&0xff);
	// 低位字节不变，其它高位取反,
	printf("%#x\n",x^(~0xff));
	//  x 的最低有效字节设置成全 1,其他字节都保持不变。[0x876543FF]
	printf("%#x\n", x|0xff);
}
//当要移的位数大于数字位数，是取余实现的，但c并不会严格执行，java会
void show_move(void){
	int x=0x87654321;
	int y=x>>32;//32mod32=0, 向右移动0位
	 y=x<<36;//36 mod 32=4 向左移动4位
	 y=x>>40;//40 mod 32 =8
}
int main1(int argc, char const *argv[])
{
	int x=100;
	// show_int(0x00345678);
	// show_point(&x);
	const char *s="hello";
	//显示字符串每个字符的整数值，即assic值，可以通过man assic 命令在终端查看
	// show_byte((byte_point)s,strlen(s));
	show_mask();


	
	return 0;
}
void array(){
	// 声明变量的时候最好初始化，否则值不确定
	char s[5]={'0'};
	char str[]="hello";
	s[0]='a';
	s[1]='v';
	s[2]='s';
	s[3]='a';
	s[4]=0;
	// s[4]='\0';
	//C不会检查数值的下界，下面的赋值不会报错
	// s[5]='3';
	//如果要以字符串形式打印字符数组最后一个字符必需是‘\0’，和数字0等价
	printf("%s-%s--%d\n",s,str,strlen(str));
	//reverse array，只适用于英语
	int max=strlen(str)-1;
	int min=0;
	while(min<max){
		char temp=str[min];
		str[min]=str[max];
		str[max]=temp;
		min++;
		max--;
	}
	printf("the reverse of array str is %s\n",str);
	char buff[]="你好,C语言";
	printf("%d\n", strlen(buff));
}

void rand(){
	/* 随机数的演示 */
	
	time_t current=time(NULL);
	printf("current time is %u\n", current);
	//要产生随机效果，参数必须是变化的，时间就是很好的参数
	srand(current);
	//rand()是产生伪随机数的函数，每次执行结果都和第一次一样，所以执行前调用随机数种子产生器srand(int param)
	int random=rand();
	printf("the randomis %d\n", random);
}
	/* C的基本数据类型 */
int main(int argc, char const *argv[]){

	// ％d表示有符号的十进制整数
	printf("my name is %s,I'm %d\n", NAME,MAX);
	//%u 表示无符号的十进制整数
	printf("my name is %s,I'm %u\n", NAME,-20);
	// 使用const表示常量
	const  int max=20;
	// 字符串常量
	const char *str="lixiaolin";
	printf("his name is %s,he is %d\n", str,max);
	// 以下有符号整数都可以加 unsigned表示无符号整数,size_t a=unsigned int a
	int a=10;
	short b=10;
	long c=10;
	long long d=20;

	//数据类型的大小和操作系统相关，以下是32位系统下的数据大小
	printf("the size of int is %d \n",sizeof(int));
	printf("the size of short is %d \n",sizeof(short));
	// long类型的大小在不同平台不同操作系统下不一，有4个字节 有8个字节
	printf("the size of long is %d \n",sizeof(long));
	// long long 就是8个字节 表示64位
	printf("the size of long long is %d \n",sizeof(long long));
	//有符号short 最小负数,h是用来修饰short类型的
	 short s=0x8001;
	printf("无符号的s值为%hu，有符号的s值为%hd,十六进制为%hx\n", s,s,s);
	//char类型是一个字节大小，有符号
	char cc=127;
	cc=cc+5;
	printf("%d\n", cc);
	//使用volatile 关键字修饰变量是告诉CPU这个变量可能被CPU之外的指令修改不要对这个变量优化代码，
	volatile int v;
	// 如果不用voaltile下面代码会合并成v＝v＋30；
	v=v+10;
	v=v+20;
	//register关键字 表示这个变量在寄存器里而不是内存中，但是建议型指令而不是命令型指令，当寄存器不够用会忽略
	register int r=0;
	scanf("%d",&a);
	
	printf("you print %d\n",a);
	return 0;
}