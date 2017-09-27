#include "util/cpp11ExternTemplate.h"

void zPrint()
{
    fun1<int>(1);
    fun2<int>(1);

    ZCpp11ExternTemplateTest1<int> obj1;
    obj1.test(0);
}