#include <thread>
#include <iostream>
#include <string>
#include <deque>
#include <mutex>
#include <functional>
#include <fstream>
#include <condition_variable> // 条件变量

using namespace std;

deque<int> dq;
mutex mu;
condition_variable cond; // 条件变量确保线程的正确执行

// 数据的生产者
void function_1()
{
    int count = 10;
    while(count > 0){
        unique_lock<mutex> locker(mu);
        dq.push_front(count);
        cout<< "t1: "<< count << endl;
        locker.unlock();
        // cond.notify_one(); // 激活一个等待这个条件的线程
        cond.notify_all();
        this_thread::sleep_for(chrono::seconds(1)); // 空闲一秒时间可以用到别线程操作..
        cout<< "new t1: "<< count << endl;
        count--;
        cout<< "new new t1: "<< count << endl;
    }
}



// 数据消费者
void function_2()
{
    int data = 0;
    while(data != 1){
        unique_lock<mutex> locker(mu);
        // 函数2可能被伪激活， 因此 ，传入lambda表达式作为第二个参数控制
        cond.wait(locker, [](){return !dq.empty(); } ) ;  // 基本和python一样lambda匿名函数都有了
        data =  dq.back();
        dq.pop_back();
        locker.unlock(); 
        cout<< "t2 got a value from t1: " <<data << endl;
    }
}


int main()
{
    thread t1(function_1);
    thread t2(function_2);

    t1.join();
    t2.join();

    return 0;

}

