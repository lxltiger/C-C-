#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <signal.h>

using namespace std;

//一般定义变量方式，需要明确类型
void case1()
{
    string str = "hello";
    map<int, string> m = {{1, "a"}, {1, "b"}};
    map<int, string>::const_iterator iter = m.begin();
}

//使用auto在编译阶段根据值自动推导类型，
void case2()
{
    auto i = 1;
    auto d = 1.0;
    auto str = "hello";
    //这个自动推导不出来
    map<int, string> m = {{1, "a"}, {1, "b"}};
    //如果上面的map变成了unordered_map，其它的都需要变，这就避免对类型的硬编码
    auto iter = m.begin();
}

//auto 的“自动推导”能力只能用在“初始化”的场合，变量右边必须要有一个表达式（简单、复杂都可以
void case3()
{
    //推导x为long类型
    auto x = 0L;
    //推导y为long*类型
    auto y = &x;
    //推导z为long*类型
    auto z{&x};
}

class X final
{
    //auto a = 10;类中不可以使用自动推导
    int a = 10;
};

//auto 总是推导出“值类型”，绝不会是“引用”；
//auto 可以附加上 const、volatile、*、& 这样的类型修饰符，得到新的类型
void case4()
{
    auto x = 10L;
    auto &x1 = x;       //推导出等式右边为long类型，x1就是long&
    auto *x2 = &x;      //推导出等式右边指针的值为long类型，使用*将其解释为long*
    const auto &x3 = x; //x3为const long&
    auto x4 = &x3;      //等式右边取x3的指针，所以x4为const long*

    cout << *x2 << endl;
    cout << *x4 << endl;
    // cout << typeid(x4).name() << endl;
}
//因为auto关键字的自动推导只能用于初始化，范围较小
//decltype可以像函数一样实现类型推导，不需要表达式，使用范围更广，更像一种自动计算
//decltype 不仅能够推导出值类型，还能够推导出引用类型，也就是表达式的“原始类型“
void case5()
{
    int x = 0;
    decltype(x) x1; //算出x类型为int，所以x1等到的就是int类型
    decltype(x) *x2;
    decltype(x) &x3 = x; //引用需要赋值
    decltype(&x) x4;     //算出类型为int*，x4为int*
    decltype(&x) *x5;    //算出类型为int*，x5为int**

    //把decltype看成类型名
    using int_ptr = decltype(&x);
    using ref_ptr = decltype(x) &;
}
//C++14 使用auto作为返回值类型的占位符，灵活

#if 0
auto get_a_set()
{
    set<int> s = {1, 2, 3};
    return s;
}
#endif

void case7()
{
    vector<int> v = {2, 3, 5, 7, 11};
    // 常引用方式访问元素，避免拷贝代价 并且不会修改值
    for (const auto &i : v)
    {
        cout << i << ",";
    }

    cout << endl;

    for (auto &i : v)
    {
        i++;
    }
}
//类定义中不能用auto，这是decltype大显身手的地方
class Demo final
{
public:
    using set_type = set<int>;

public:
    //使用decltype计算函数指针类型
    using sig_func_ptr_t = decltype(&signal);

private:
    set_type m_set;
    using iter_type = decltype(m_set.begin());
    iter_type m_pos;
};

int main(int argc, char const *argv[])
{
    case1();
    case2();
    case3();
    case4();
    case5();
    case7();
    return 0;
}
