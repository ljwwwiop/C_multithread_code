// 数据竞争
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

// 定义互斥对象
mutex mu;

// 通过互斥对象同步cout,但如果出现异常,mu将永远的锁住，不推荐使用
void shared_print(string msg, int id){
    mu.lock();
    cout<< msg << id << endl;
    mu.unlock();
}

// 通过lock_guard同步cout, 无论是否发生异常，函数调用结束后，mu对象都能自动地被解锁
// 但cout做为全局变量，并没有完全在mu的保护下，任然会被其他线程在不加锁的情况下调用

// void shared_print(std::string msg, int id) {
//     std::lock_guard<std::mutex> guard(mu);
//     std::cout << msg << id << std::endl;
// }

void function()
{
    for(int i = 0; i > -100 ;i--){
        shared_print("From t1: ",i);
    }
}

int main()
{
    thread t1(function);
    for(int i = 0;i < 100;i++)
        shared_print("from main: ",i);

    t1.join();
    return 0;
}





