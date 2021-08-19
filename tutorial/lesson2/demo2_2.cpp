#include <iostream>
#include <thread>
#include <string>

using namespace std;

void function()
{
    cout<<" hello world"<<endl;
}

class Factor{
public:
    void operator()(string &msg){
        for(int i = 0; i > -5;i--)
        {
            cout<<"from t1: "<< msg<<endl;
            msg = "l love thread code !";
        }
    }

};

int main()
{
    string s = "doge doge meme";
    cout<< this_thread::get_id() <<endl;
    thread t1( (Factor()), ref(s) ); // 字符串s为引用传递

    cout<< t1.get_id() << endl;
    thread t2 = move(t1); // 转移线程
    cout<< t2.get_id() << endl; // id 依然与t1中相同，因为已经移进去
    
    t2.join();
    
    // 返回基于cpu 数目或者cpu内核数目的同一时刻在物理机器上运行的线程数
    cout<<"this is pc has: "<< thread::hardware_concurrency() << endl;
    return 0;

}



