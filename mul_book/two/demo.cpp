#include <iostream>
#include <thread>
#include <string>

// 三种创建线程的方式
/*
    join() 主要是主线程和子线程会和，执行完毕后再继续，主要就是阻塞和等待
    detach() 分离，让子线程不用在和主线程回合可以直接继续向下执行

*/
using namespace std;

void function()
{
    cout<<"this is thread "<<endl;
}

class A{

public:
    int m_i;
    A(int &i) : m_i(i)
    {
        cout<<"A() 构造函数"<<endl;
    }
    ~A(){
        cout<<"A 析构函数"<<endl;
    }
    A(const A &a) : m_i(a.m_i)
    {
        cout<<"拷贝构造函数"<<endl;
    }

    void operator()(){
        // 重载() 不带参数的
        cout<<"m_i : "<<m_i<<endl;
    }



};


int main(){
    int x = 6;
    A a(x);

    printf("----------\n");
    thread t1(function);
    thread t2(a);

    if(t1.joinable())
    {
        cout<<"1:joinable() == true"<<endl;
    }
    else{
        cout<<"2:joinable() == false" <<endl;
    }

    //t1.join(); // 阻塞主线程，并且等待function子线程执行完成
    t1.detach();
    t2.detach();
    // 一旦调用了detach就不可以用join(),否则bug
    if(t1.joinable())
    {
        cout<<"ture"<<endl;
    }
    else{
        cout<<"false"<<endl;
    }

    if(t2.joinable())
    {
        cout<<"t2 ture"<<endl;
    }
    else{
        cout<<"t2 false"<<endl;
    }

    cout<<"this is main thread"<<endl;


    return 0;
}
