#include<iostream>
#include <thread>
#include <string>

using namespace std;

void function()
{
    cout<<" hello world"<<endl;
}

class Factor{
public:
    void operator()(string& msg ){
        // 引用形式的参数
        cout<< "from t1:"<< msg << endl;
        msg = "l love threadcode";
        
    }

};


int main()
{
    string s = "meme doge";
    string &p = s;
    string *ptr = &s;
    int len = (*ptr).size();


    // 在线程t1中传入类的第一种方式
    // Factor fct;
    // thread t1(fct,s);

    //在线程t1中传入类的第二种方式,与第一种等效
    thread t1((Factor()),ref(s));

    // thread t1((Factor()), ref(s)); //字符串s为引用传递

    cout<< "from main: "<< s <<endl;
    cout<< "from main: p "<< p <<endl;
    cout<< "address:  "<< ptr <<endl;
    cout<< "ptr[0]:  "<< *ptr <<endl;
    cout<< "len:  "<< len <<endl;
    cout<<"s[3] "<<(*ptr)[3]<<endl;

    try{
        for(int i = 0;i<5;i++)
        {
            cout<< "from main: - "<< i<<endl;
        }
    }catch(...){
        t1.join();
        throw;
    }

    t1.join();

    return 0;

}



