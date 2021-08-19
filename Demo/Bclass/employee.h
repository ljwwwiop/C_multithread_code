#ifndef __EMPLOYEE_H_
#define __EMPLOYEE_H_

#include <iostream>
#include <string>

using namespace std;

class Employee{
    friend class Intermediar;
public:
    Employee();
    Employee(int age,string name);
    ~Employee();

    void Register(int age,string name, int salary);
    void SearchJob(string job);
    void show();

protected:
    void PersonInfo(string tel, string home);

private:
    int m_Age;
    string m_Name;
    string m_Job;
    string m_Home;
    int m_Salary;
    string m_Tel = "";

};

class Intermediar : public Employee{
    
public:
    Intermediar(string name,int age,Employee* employ);
    ~Intermediar();

    void Show();

    void operator()(int x,int y){
        cout<< x + y<<endl;
    }

private:
    string m_Name;
    int m_Age;
    Employee* employee;

};


#endif