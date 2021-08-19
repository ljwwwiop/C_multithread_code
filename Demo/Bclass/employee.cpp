#include "employee.h"

Employee::Employee()
{
    m_Age = 0 ;
    m_Home = "";
    m_Job = "";
    m_Salary = 0;
    m_Tel = "";
    m_Name = "";

}

Employee::~Employee(){}

Employee::Employee(int age, string name)
{
    m_Age = age ;
    m_Home = "";
    m_Job = "";
    m_Salary = 0;
    m_Tel = "";
    m_Name = name;
}

void Employee::PersonInfo(string tel, string home)
{
    m_Tel = tel;
    m_Home = home;
    printf("****reigster person info done !******\n");
}

void Employee::Register(int age,string name, int salary)
{

}

void Employee::SearchJob(string job)
{
    if(job == "Coder" ){
        cout<<m_Name<<" ";
        printf("yes, there is have\n");
    }else{
        cout<<m_Name<<" ";
        printf("haven't jobs\n");
    }
}

void Employee::show()
{
    cout<<m_Age<<" "<<m_Name<<" "<<m_Home<<" "<<m_Tel<<endl;
}

Intermediar::Intermediar(string name,int age, Employee* employ )
    :  Employee(age,name)
{
    m_Name = name;
    m_Age = age;
    employee = employ;
    employee->m_Age = m_Age;
    employee->m_Name = m_Name;
    employee->PersonInfo("110110100","XiaMen");
}

Intermediar::~Intermediar()
{

}

void Intermediar::Show()
{
    cout<<m_Name<<" "<<m_Age<<endl;
    employee->show();
}





