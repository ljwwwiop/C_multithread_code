#ifndef __PRODUCT_H_
#define __PRODUCT_H_

#include <iostream>
#include <string>

using namespace std;

class Boss{
public:
    Boss();
    Boss(int age,string name, string job);
    ~Boss();

    void HasJob();
    bool IsPass(string job);

private:
    string m_name;
    string m_job;
    int m_age;


};

#endif