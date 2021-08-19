// 实现有时间限制的等待

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <future>
#include <deque>
#include <chrono>

using namespace std;

int factorial(int N)
{
    int res = 1;
    for(int i = N;i>1;i--)
        res *= i;
    cout<<"Result : "<<res<<endl;
    return res;
}


int main()
{
    // 实现对线程的时间限制
    thread t1(factorial , 6);
    //std::this_thread::sleep_for(std::chrono::milliseconds(3));
    chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + chrono::milliseconds(10);
    this_thread::sleep_until(tp);   // 进行设定时间等待

    // 实现对timed_mutex 的时间限制
    std::timed_mutex mu;
    if(mu.try_lock_for(chrono::milliseconds(3)))
    {
        cout<< " try lock: "<<endl;
        mu.unlock();
    }

    if(mu.try_lock_until(tp))
    {
        cout<<" lock until : "<<endl;
        mu.unlock();
    }

    // 实现对条件变量的时间限制！！
    mutex mu2;
    unique_lock<mutex> locker2(mu2); 
    condition_variable cond;
    cond.wait_for(locker2, chrono::milliseconds(3));
    cond.wait_until(locker2,tp);

    // 实现对future的时间限制
    promise<int> p;
    future<int> f = p.get_future();
    f.wait_for(chrono::milliseconds(3));
    f.wait_until(tp);

    t1.join();

    return 0;
}




