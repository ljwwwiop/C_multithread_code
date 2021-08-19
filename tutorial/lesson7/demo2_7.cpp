#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <future>

using namespace std;

/*
    future从异步任务中获取结果，一般于async配合使用,async创建异步任务
*/

int factorial(future<int> &f)
{
    int res =1;
    int N = f.get();
    for(int i = N;i > 1;i--)
        res *= i;
    
    cout<< "Result : "<<res<<endl;
    return res;
}

int main()
{
    int x;
    promise<int> p;// 想要从主线程中传入子线程得变量
    future<int> f = p.get_future();

    // async() 第一个参数 线程创建得决策：一种立即创建 launch::async, 一种延迟加载创建deferred 直到调用了future得get 或者wait时才创建线程.
    future<int> fu = async(launch::async, factorial, ref(f));

    p.set_value(4);
    x = fu.get();

    cout<<"res : "<<x<<endl;

    return 0;
}



