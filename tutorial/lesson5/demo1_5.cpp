#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

#include <typeinfo>

using namespace std;

class LofFile{
public:
    LofFile()
    {

    }

    // 延迟初始化 lazy init
    void shared_print(string id,int value)
    {
        // 

        // 当共享数据只有再初始化时才需要并发访问的保护，但在此之后却不需要显式同步时使用
        // 此方法可以避免二次检查锁定 
        call_once(m_flag, [&](){m_f.open("./log.txt");} );

        // 方便加锁解锁，但性能不如lock_guard
        unique_lock<mutex> locker(m_mutex,defer_lock);

        // ..
        locker.lock();
        m_f << "from "<<id << " : "<< value << endl;
        locker.unlock();
        // 

        // 移动: 在做用域之前转移锁的所有权
        unique_lock<mutex> locker2 = move(locker);

    }


private:
    mutex m_mutex;
    once_flag m_flag;
    ofstream m_f;

};

void function_1(LofFile& log) {
    for (int i = 0; i > -5; i--)
        log.shared_print("From t1: ", i);
}

int main()
{   
    int a = 1;
    if(typeid(a) == typeid(int)) cout<< " a : "<<a <<endl;

    LofFile log;
    thread t1(function_1,ref(log));

    for(int i = 0; i< 5;i++)
        log.shared_print("main : ",i);
    
    t1.join();

    return 0;
}

