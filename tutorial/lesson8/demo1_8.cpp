#include <mutex>
// #include <iostream>
#include <future>
#include <fstream>

using namespace std;

// 8种线程创建方式总结

class A{
public:
    A(){}
    void f(int a, char c){ }
    int operator()(int N){return 0;} // 函数重载()

};


void foo(int x)
{

}

int main()
{
    A a;
    thread t1(a,6); // 传递a的拷贝给子线程
    thread t2(ref(a) , 6); // 传递a的引用给子线程
    thread t3(move(a) , 6); // 移动对象a到子线程
    thread t4(A() , 6); // 传递临时创建的a对象给子线程

    thread t5(foo,6); // 通知已知函数创建子线程
    thread t6( [](int x){ return x*x;},6 ); // 传递lambda匿名函数创建子线程
    thread t7(&A::f, a, 8 , 'w'); // 传递a的拷贝的成员函数给子线程
    thread t8(&A::f, &a, 8, 'w'); // 传递a的地址的成员函数给子线程，供子线程创建

    async(launch::async, a, 6); // 和以上都类似可以

    return 0;

}

