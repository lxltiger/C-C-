#include <iostream>
#include <string>
#include <typeinfo>
#include <stdexcept>
#include <type_traits>

using namespace std;

template<int N>
struct fib
{
    static_assert(N>0,"N must be positive");
    static const int value=fib<N-1>::value+fib<N-2>::value;
};

template<>
struct fib<0>
{   
    static const int value=1;
};

template<>
struct fib<1>
{   
    static const int value=1;
};

[[gnu::deprecated]]
int old_func(){
    return -1;
}

[[gnu::constructor]]
void first_fun(){
    printf("before main()\n");
}

[[gnu::destructor]]
void last_func()
{
    printf("after main()\n");
}

[[gnu::always_inline]] inline
int get_num(){
    return 42;
}

//抑制没有返回值的警告 exit函数也用
[[noreturn]]
int case1(bool flag){
    throw std::runtime_error("xxx");
}
//static_assert 运行在编译阶段，只能看到编译时的常数和类型，看不到运行时的变量、指针、内存数据等，是“静态”的，在编译阶段检查错误，
template<typename T>
void check_type(T v){
    // static_assert(is_integral<T>::value,"int");
    //static_assert(is_default_constructible<T>::value, "is_default_constructible");

    static_assert(is_pointer<T>::value,"ptr");
    cout<<"static_assert:"<<typeid(v).name()<<endl;
    cout<<"is_void:"<<is_void<T>::value<<endl;
}

int main(int argc, char const *argv[])
{
    check_type((void *)10);
    return 0;
}

