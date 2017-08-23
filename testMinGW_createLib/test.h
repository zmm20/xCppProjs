#pragma once

#define MYTEST_NAMESPACE_BEGIN namespace MyPoppler {
#define MYTEST_NAMESPACE_END }



#ifndef Dll_ISECOCRFORTESS
#define DllAPI __declspec(dllimport)   
#else   
#define DllAPI __declspec(dllexport) 
#endif

#include <string>


MYTEST_NAMESPACE_BEGIN

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DllAPI int add(int a, int b);
DllAPI std::string hello(std::string name); // 测试标准容器

#ifdef __cplusplus
}
#endif /* __cplusplus */


class DllAPI CMyClass
{
public:
	CMyClass();
	void hello(const char* name, int len);
	void hello(const std::string& name);
};

MYTEST_NAMESPACE_END