#include <stdio.h>
// 在头文件中实现自定义函数
#include "function.h"
//自定义函数，必需放在main函数前
int mystrlen(char buf[]){
	int len=0;
	while(buf[len++]);
	return --len;
}

unsigned long long factorial(int n){
	
	if(n==1){
		return 1;
	}else {
		return n*factorial(n-1);
	}
	
}
void getFactorial(){
	int number=0;
	//不能加回车符
	scanf("%d",&number);
	
	if(number>0){
		unsigned long long result=factorial(number);
		printf("%llu\n", result);
	}else{
		printf("%s\n", "请输入大于0的数");
	}
}
//十进制转二进制
void binary(int n){
	
	if(n>0){
		binary(n/2);
		char c=n%2+'0';
		printf("%c\n", c);
	}
}

char toChar(int n){
	switch (n){
		case 15: return 'f';
		case 14: return 'e';
		case 13: return 'd';
		case 12: return 'c';
		case 11: return 'b';
		case 10: return 'a';
		default:return n+'0';
	}
}
//十进制转16进制
void to_hex(int n){
	if(n>0){
		to_hex(n/16);
		int temp=n%16;
		printf("%c", toChar(temp));
		
	}
}

//求斐波拉数
int fib(int n){
	int number=0;
	if(n==1){
		number= 0;
	}else if(n==2){
		number= 1;
	}else{		
		number=fib(n-1)+fib(n-2);
	}
	return number;
}

int main(int argc, char const *argv[])
{
	// binary(11);
	// to_hex(100);
	int a=fib(5);
	// printf("the result is %d\n", a);
	return 0;
}



