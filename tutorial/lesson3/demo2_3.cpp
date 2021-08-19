#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>


using namespace std;

class LofFile{
public:
    LofFile(){
        m_f.open("log.txt");
    }
    void shared_print(string id, int value)
    {
        lock_guard<mutex> locker(m_mutex);
        m_f << "from "<< id << ": "<<value<<endl;
    }

private:
    mutex m_mutex;
    ofstream m_f;

};

void function(LofFile &log)
{
    for(int i = 0;i>-5;i--){
        log.shared_print("from t1: ",i);
    }
}


int main()
{
    LofFile log;
    thread t1(function,ref(log));

    for(int i =0;i<15;i++)
        log.shared_print("main: ",i);
    
    t1.join();

    return 0;
}

