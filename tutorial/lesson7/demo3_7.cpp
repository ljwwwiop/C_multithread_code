#include <iostream>
#include <future>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

int factorial(shared_future<int> f)
{
    int res = 1;
    int N = f.get();
    for(int i = N;i >1;i--)
        res *= i;
    
    cout<<"Result : "<<res<<endl;
    return res;
}

int main()
{
    promise<int> p; // 想要从主线程中 传入子线程的变量
    future<int> f = p.get_future();
    shared_future<int> sf = f.share(); // shared_future 可以拷贝

    future<int> fu = async(launch::async,factorial,sf);
    future<int> fu2 = async(launch::async,factorial,sf);
    future<int> fu3 = async(launch::async,factorial,sf);

    p.set_value(4);

    return 0;
}


