#include <thread>
#include <iostream>
#include <mutex>
#include <string>
#include <deque>
#include <future>
#include <fstream>
#include <functional>

using namespace std;
/*
    packaged_task 与 promise 区别 一个 保存过程一个保存值
*/
deque<packaged_task<int()>> task_q;
mutex mu;
/*由于task_q定义为全局，会存在主线程和子线程的数据竞争，所以需要引入条件变量进行保护*/
condition_variable cond;

int factorial(int N)
{
    int res = 1;
    for(int i = N ;i > 1;i--)
        res *= i;
    cout<<"Result : "<<res<<endl;
    return res;
}

void thread_1()
{
    packaged_task<int()> t;
    {
        // 引入条件变量,对应的所对象则应改为unique_lock
        unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){return !task_q.empty();} );
        t = move(task_q.front());
    }
    t();
}


int main()
{
    thread t1(thread_1);
    // 形参类型都要删除，将int (int ) 改为int()
    packaged_task<int()> t( bind(factorial,6));
    future<int> ret = t.get_future();
    {
        lock_guard<mutex> locker(mu);
        task_q.push_back(move(t));
    }
    
    cond.notify_one();
    int value = ret.get();
    cout<< "value : "<<value<<endl;
    t1.join();
    return 0;
}



