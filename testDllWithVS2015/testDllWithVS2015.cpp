// testDllWithVS2015.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#ifdef TESTDLLWITHVS2015_EXPORTS
#define DllAPI __declspec(dllexport) 
#else   
#define DllAPI __declspec(dllimport)   
#endif


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    DllAPI int test(int a, int b)
    {
        return a + b;
    }

#ifdef __cplusplus
}
#endif 