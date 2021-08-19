#include "product.h"

#define C "Coder"
#define D "Cooker"


Boss::Boss()
{
    m_name = "ben";
    m_job = "Coder";
    m_age = 23;
}

Boss::~Boss(){

}

Boss::Boss(int age,string name, string job)
{
    m_name = name;
    m_age = age;
    m_job = job;
}

void Boss::HasJob()
{
    if(m_job == C){
        cout<<m_name<<" ";
        printf("yes , there is need coder!\n");
    }else if(m_job == D){    
        cout<<m_name<<" ";
        printf("yes, we need a cooker \n");
    }else{
        cout<<m_name<<" ";
        printf("sorry, we haven't jobs\n");
    }
}

bool Boss::IsPass(string job)
{
    if( job == C)
    {
        if( m_age < 30){
            printf("ok successful\n");
        }
        else{
            printf("sorry \n");
        }
    }
}


