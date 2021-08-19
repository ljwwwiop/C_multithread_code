#include <iostream>
#include <thread>

using namespace std;
// 调式时候节得加上-lpthread 不然编译不过 用到了posix实现的先冲
void function_()
{
    std::cout<<"hello world --"<<std::endl;
}

void s1(int &a){
    for(int i = 0;i<10;i++)
    {
        cout<<"s1 :"<<i<<endl;
        a = i;
    }
}

void s2()
{
    for(int i = 0 ; i>-10;i--)
        cout<<"s2 :"<<i<<endl;
}

int main()
{
    // std::thread t1(function_);
    // t1.detach();
    int x = 20;
    thread t2(s2);
    thread t1(s1,ref(x));
    for(int i = 10 ;i >0;i--)
    {
        x = i;
        cout<<"main x :"<<x<<endl;
    }

    // if(t1.joinable())
    // {
    //     t1.join();
    // }

    t1.join();
    t2.join();

    return 0;
}

