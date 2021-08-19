//  死锁问题的产生和避免死锁的一般方法
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

class LofFile{
public:
    LofFile(){
        m_f.open("./log.txt");
    }

    void shared_print(string id,int value)
    {
        lock(m_mutex,m_mutex2);
        // 分配两把锁
        lock_guard<mutex> locker(m_mutex, adopt_lock);
        lock_guard<mutex> locker2(m_mutex2, adopt_lock);
        m_f<< "from "<< id <<" : "<< value << endl;
    }

    void shared_print2(string id,int value)
    {
        lock(m_mutex,m_mutex2);
        lock_guard<mutex> locker2(m_mutex2, adopt_lock);
        lock_guard<mutex> locker(m_mutex, adopt_lock);
        cout<< "from "<< id <<" : "<< value << endl;
    }

private:
    mutex m_mutex;
    mutex m_mutex2;
    ofstream m_f;
};

void function(LofFile &log)
{
    for(int i = 0; i> -5;i--)
    {
        log.shared_print("from t1: ",i);
    }
}

int main()
{
    LofFile log;
    thread t1(function,ref(log));

    for(int i = 0;i<5;i++)
    {
        log.shared_print2("main : ",i);
    }

    t1.join();
    return 0;
}

