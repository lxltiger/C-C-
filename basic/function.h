// 一般在头文件中声明函数
//为了防止头文件在一个c文件中被多次include调用导致重复预编译，使用以下标准声明
#ifndef _He_
#define _He_ 
int mystrlen(char buf[]);

#endif