#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <future>

using namespace std;
// 将子线程中的变量传入主线程

int factorial(int N)
{
    int res = 1;
    for(int i = N;i > 1;i--)
        res *= i;
    
    cout<<"res : "<<res<<endl;

    return res;
}

int main()
{
    int x ;

    // future<int> fu = async(launch::async| launch::deferred, factorial,4);
    future<int> fu = async(launch::deferred, factorial,4);
    x = fu.get(); // get() 函数会等待子线程结束，然后将返回值传给x，并且future对象只能被调用一次

    return 0;
}

