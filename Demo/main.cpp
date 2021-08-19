#include "Aclass/product.h"
#include "Bclass/employee.h"

int main()
{
    printf("hello world!\n");
    Boss boss;
    Boss boss2(20,"peter","Cooker");
    boss2.HasJob();
    boss2.IsPass("Coder");
    printf("address : %p \n", &boss2);

    Boss* boss3 = new Boss();
    printf("address : %p \n", &boss3);
    boss3->HasJob();

    Employee employee(28,"jack");
    Employee *employee2 = new Employee(45,"bob");

    employee.Register(28,"jack",5000);
    employee.SearchJob("Coder");

    employee2->SearchJob("faker");

    Intermediar inter("faker",98,employee2);
    inter.Show();
    inter(98,2);


    delete boss3;
    delete employee2;

    printf("done !\n");
    printf("address : %p \n", &boss3);

    return 0;
}


