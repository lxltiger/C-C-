#include <iostream>

using namespace std;
/* 
预编译就是把include中的头文件替换过来并去掉注释
文件的路径最好不要含中文等特殊字符
gcc -E -o fileName sourceFileName   -E  预编译 －o 输出的文件名
例如预编译本文件
g++  -E -o a.cxx  preprocess.cpp

查看编译器提供的宏定义
g++ -E -dM - < /dev/null
输出如下
#define __GNUC__ 5
#define __unix__ 1
#define __x86_64__ 1
#define __UINT64_MAX__ 0xffffffffffffffffUL...
 */

void case1()
{
# // 预处理空行
#if __linux__
#   define HAS_LINUX 1 //有缩进
#endif 

#if __cplusplus >=201402
    cout<<"c++14 or later"<<endl;
#elif __cplusplus >= 201103
    cout << "c++11 or before" << endl;
#else 
#   error "c++ is to old"
#endif

#ifndef NDEBUG
    cout << "debug mode" << endl;
#endif  // NDEBUG
#
    cout << "linux is " << HAS_LINUX << endl;
}
//宏是没有作用域概念的，永远是全局生效。所以，对于一些用来简化代码、起临时作用的宏，最好是用完后尽快用“#undef”取消定义，避免冲突的风险
void case2()
{
#define CUBE(a) (a)*(a)*(a)    
    cout<<CUBE(10)<<endl;
#undef CUBE

#ifdef AUTH_PWD
# undef AUTH_PWD
#endif
#define AUTH_PWD "123"

    cout<<AUTH_PWD<<endl;

}

/* 
为了防止代码被重复包含，通常要加上“Include Guard”，也就是用“#ifndef/#define/#endif”来保护整个头文件
 #ifndef _XXX_H_INCLUDED_
  #define _XXX_H_INCLUDED_

  ...    // 头文件内容

  #endif // _XXX_H_INCLUDED_
*/
#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE(x)  }

BEGIN_NAMESPACE(my_own)
class MyClass final
{
};

void case3()
{
    cout<<"work in my own"<<endl;
}

END_NAMESPACE(my_own)



int main(int argc, char const *argv[])
{
    case1();
    case2();

    my_own::case3();
    [[gnu::unused]]
    my_own::MyClass obj;
    return 0;
}
