#include <iostream>
#include <string>
#include <vector>
#include <set>

#if 1
class Interface
{
};


/* 
和Java一样，final可以防止继承
在必须使用继承的场合，只使用 public 继承，避免使用 virtual、protected  
使用private继承， 父类的protected和public属性在子类中变为private；
使用protected继承，父类的protected和public属性在子类中变为protected；
使用public继承， 父类的protected和public属性不发生改变;
 */
class Implement final : public Interface
{
public:
    using super_type = Interface;
    using this_type = Implement;

private:
};

#endif

#if 1

struct KafakaConfig final
{
    int id;
    std::string ip_addr;
};

class Demo final
{
//使用类型别名  简化代码  方便替换，比如把set改成unordered_set
public:
    using this_type = Demo;
    using Kafaka_config_type = KafakaConfig;

public:
    using string_type = std::string;
    using uint32_type = uint32_t;

    using set_type = std::set<int>;
    using vector_type = std::vector<std::string>;

public:
//对于比较重要的构造函数和析构函数，应该用“= default”的形式，明确地告诉编译器使用默认实现
    Demo() = default;
    ~Demo() = default;

    //= delete明确地禁用某个函数形式，而且不限于构造 / 析构，可以用于任何函数（成员函数、自由函数）
    Demo(const Demo &) = delete;//禁止拷贝构造
    Demo &operator=(const Demo &) = delete;//禁止拷贝赋值

public:
    //对了防止隐式构造和隐式转换，对于单参数的构造函数，或者是转型操作符函数 使用explicit修饰
    explicit Demo(const string_type &str)
    {
        m_name = str;
    }
    explicit operator bool()
    {
        return !m_name.empty();
    }

public:
    void set_name(const string_type &str);

private:
    string_type m_name = "tom";
    uint32_type m_age = 23;
    set_type m_books;
    std::vector<int> v{1, 2, 3};

private:
    Kafaka_config_type m_conf;
};

#endif

#if 1

class DemoDelegating final
{
private:
    int a;
//委托构造，和Java的方法重载差不多
public:
    DemoDelegating(int x) : a(x)
    {
    }

    DemoDelegating() : DemoDelegating(0)
    {
    }

    DemoDelegating(const std::string &s) : DemoDelegating(std::stoi(s))
    {
    }
};

#endif

int main(int argc, char const *argv[])
{
    using namespace std;

    cout << "show your class." << endl;
    return 0;
}
