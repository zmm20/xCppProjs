#include "test.h"
#include <iostream>

using namespace std;

MYTEST_NAMESPACE_BEGIN

int add(int a, int b)
{
	return a + b;
}

std::string hello(std::string name)
{
	std::string ret = "hello " + name;
	return ret;
}

CMyClass::CMyClass()
{
}
void CMyClass::hello(const char* name, int len)
{
	std::string n(name, name + len);
	
	cout << n << endl;
}
void CMyClass::hello(const std::string& name)
{
	cout << name << endl;
}

MYTEST_NAMESPACE_END