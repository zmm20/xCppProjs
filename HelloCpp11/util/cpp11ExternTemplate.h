#pragma once

#include <iostream>

template <typename T>
void fun1(T t) {
#pragma message("fun1 ���ڱ���...")

    std::cout << "fun1" << std::endl;
}
// c++11 �ⲿģ��, �������߱���Ч��
// ������, ���˸þ仰֮��, "fun1 ���ڱ���..." ֻ��ӡ��һ��, �� "fun2 ���ڱ���..." ��ӡ��2��
// , �ɼ�����һ���ǿ�����߱���Ч�ʵ�
extern template void fun1<int>(int);

template <typename T>
void fun2(T t) {
#pragma message("fun2 ���ڱ���...")

    std::cout << "fun2" << std::endl;
}

/*
    http://www.cnblogs.com/lvdongjie/p/4489907.html
    1. ����ⲿģ��ָ�������һ�����뵥Ԫ�У���ô��֮��Ӧ����ʾʵ���������������һ�����뵥Ԫ�л���ͬһ�����뵥Ԫ�ĺ��������С�
    2. �ⲿģ��ָ�������һ����̬���������ļ��������������������ྲ̬��������ע����һ�����Զ��׼��ģ���Ϊ��̬����û���ⲿ�������ԣ��������ڱ����뵥Ԫ֮����֣���
    3. �ⲿģ��ָ��Ӧ������ĳ�Ա���������౾����ע����Ȼ�Ѿ�������������г�Ա�ˣ�Ҳ���൱�����������ˣ�
    4. �ⲿģ��������������Ƿ����ã�û����ȷ�涨��������������ʵ�֡�
*/
template <typename T>
class ZCpp11ExternTemplateTest1
{
public:
    void test(T x)
    {
        std::cout << "ZCpp11ExternTemplateTest1 test " << std::endl;
    }
};
extern template class ZCpp11ExternTemplateTest1<int>;